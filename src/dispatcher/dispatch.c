/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 22:26:08 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a pipe and store its endpoints.
 * @param fd Output array where fd[0]=read end and fd[1]=write end.
 * @return true on success, false on failure.
 */
static bool	create_pipe(int *fd)
{
	int	new_fd[2];

	if (pipe(new_fd) == -1)
		return (false);
	fd[0] = new_fd[0];
	fd[1] = new_fd[1];
	return (true);
}

static int	spawn_child(t_shell *shell, t_ast *ast)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child_process(ast, shell);
	if (shell->fd[2] != STDIN_FILENO)
		close(shell->fd[2]);
	shell->children++;
	return (pid);
}

static int	wait_children(t_shell *shell, int pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	set_execution_signals();
	while (shell->children--)
	{
		if (wait(&status) == pid)
		{
			exit_code = get_exit_code(status);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
		}
	}
	return (exit_code);
}

/**
 * @brief Dispatch execution of an AST.
 *
 * Executes pipelines by forking one child per left segment and a final child
 * for the last command, wiring pipe endpoints between them. If the AST is a
 * single command and it is a builtin, executes it in the parent so it can
 * modify the shell environment.
 *
 * @param ast Parsed AST.
 * @param shell Shell context (env + last status).
 * @return Exit status of the last pipeline command (or builtin status).
 */
int	dispatch(t_shell *shell)
{
	t_ast	*ast;
	int		pid;

	ast = shell->ast;
	create_heredocs(shell);
	while (ast->node.type == NODE_PIPE)
	{
		if (!create_pipe(shell->fd))
			return (-1);
		expand_tokens((&ast->node.left->leaf.argv), shell);
		pid = spawn_child(shell, ast->node.left);
		close(shell->fd[1]);
		shell->fd[1] = -1;
		shell->fd[2] = shell->fd[0];
		shell->fd[0] = -1;
		ast = ast->node.right;
	}
	expand_tokens(&(ast->leaf.argv), shell);
	if (ast->leaf.argv && shell->children == 1
		&& is_builtin(ast->leaf.argv->content) != -1)
		return (exec_builtin(ast, shell, false));
	shell->fd[1] = STDOUT_FILENO;
	pid = spawn_child(shell, ast);
	return (wait_children(shell, pid));
}
