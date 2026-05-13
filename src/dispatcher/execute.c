/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:48:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 23:33:39 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute the selected builtin implementation.
 * @param builtin_id Builtin identifier returned by is_builtin().
 * @param argv Argument vector (argv[0] is the builtin name).
 * @param shell Shell context (env + last status).
 * @return Builtin exit status.
 */
int	builtin_sorter(int builtin_id, char **argv, t_shell *shell)
{
	if (builtin_id == CD)
		return (ft_cd(argv, &shell->env));
	if (builtin_id == ECHO)
	{
		ft_echo(argv);
		return (0);
	}
	if (builtin_id == ENV)
		return (ft_env(argv, shell->env));
	if (builtin_id == EXIT)
		return (ft_exit(argv, shell->last_exit_status));
	if (builtin_id == EXPORT)
		return (ft_export(argv, &shell->env));
	if (builtin_id == PWD)
		return (ft_pwd(argv));
	if (builtin_id == UNSET)
		return (ft_unset(argv, &shell->env));
	return (-1);
}

void	restore_fds(t_shell *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[3], STDOUT_FILENO);
	close(shell->fd[0]);
	close(shell->fd[3]);
}

int	exit_builtin(t_shell *shell, bool is_child, int exit_code)
{
	if (is_child)
	{
		if (shell->fd[1] != STDOUT_FILENO)
			close(STDOUT_FILENO);
		if (shell->fd[2] != STDIN_FILENO)
			close(STDIN_FILENO);
		empty_shell(shell);
		free_ast(shell->ast);
	}
	else
	{
		if (shell->fd[0] != -1)
		{
			close(shell->fd[1]);
			dup2(shell->fd[0], STDOUT_FILENO);
		}
		if (shell->fd[3] != -1)
		{
			close(shell->fd[2]);
			dup2(shell->fd[3], STDIN_FILENO);
		}
	}
	return (exit_code);
}

/**
 * @brief Execute a builtin in the parent process.
 *
 * Saves STDIN/STDOUT, applies redirections, expands tokens, builds argv and
 * runs the builtin. Restores STDIN/STDOUT before returning.
 *
 * @param ast Command AST leaf.
 * @param shell Shell context (env + last status).
 * @return Builtin exit status.
 */
int	exec_builtin(t_ast *ast, t_shell *shell, bool is_child)
{
	int		argc;
	char	**argv;
	int		builtin_id;
	int		status;

	status = 0;
	if (!is_child)
	{
		if (!redirect(ast, shell))
			return (exit_builtin(shell, is_child, 1));
	}
	argv = build_argv(ast->leaf.argv, &argc);
	if (!argv || !argv[0])
		return (free(argv), exit_builtin(shell, is_child, 0));
	builtin_id = is_builtin(argv[0]);
	status = builtin_sorter(builtin_id, argv, shell);
	return (free(argv), exit_builtin(shell, is_child, status));
}
