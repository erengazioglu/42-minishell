/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 15:35:24 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Map a command name to a builtin identifier.
 * @param str Command name (e.g. "cd", "echo").
 * @return Builtin id (e.g. @c CD) or -1 if not a builtin.
 */
int	is_builtin(char *str)
{
	if (ft_str_equals(str, "cd"))
		return (CD);
	if (ft_str_equals(str, "echo"))
		return (ECHO);
	if (ft_str_equals(str, "env"))
		return (ENV);
	if (ft_str_equals(str, "exit"))
		return (EXIT);
	if (ft_str_equals(str, "export"))
		return (EXPORT);
	if (ft_str_equals(str, "pwd"))
		return (PWD);
	if (ft_str_equals(str, "unset"))
		return (UNSET);
	return (-1);
}

void	child_process(t_ast *ast, t_shell *shell, int *fd, t_intlist **hdoc)
{
	int		argc;
	char	**argv;
	char	**paths;
	int		i;
	char	**envp;
	int			err;
	struct stat	path_stat;

	set_child_signals();
	if (!redirect(ast, fd, shell, hdoc))
		exit(1);
	if (ast->leaf.argv)
		expand_tokens(ast->leaf.argv, shell);
	argv = build_argv(ast->leaf.argv, &argc);
	if (!argv || !argv[0])
		exit(0);
	if (is_builtin(argv[0]) != -1)
		exit(exec_builtin(ast, shell, hdoc));
	envp = env_to_envp(shell->env);
	if (ft_strchr(argv[0], '/', 0, 0))
	{
		if (stat(argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_putstr("minishell: ", 2, -1, false);
			ft_putstr(argv[0], 2, -1, false);
			ft_putstr(": Is a directory\n", 2, -1, false);
			exit(126);
		}
		execve(argv[0], argv, envp);
		err = errno;
		ft_putstr("minishell: ", 2, -1, false);
		errno = err;
		perror(argv[0]);
		if (err == ENOENT)
			exit(127);
		else
			exit(126);
	}
	paths = extract_paths(*argv, shell->env);
	if (paths && !check_paths(paths))
		paths = NULL;
	execve(argv[0], argv, envp);
	i = 0;
	if (paths)
	{
		while (paths[i])
			execve(paths[i++], argv, envp);
	}
	ft_putstr(argv[0], 2, -1, false);
	ft_putstr(": command not found\n", 2, -1, false);
	exit(127);
}

/**
 * @brief Create a pipe and store its endpoints.
 * @param fd Output array where fd[0]=read end and fd[1]=write end.
 * @return true on success, false on failure.
 */
bool	create_pipe(int *fd)
{
	int	new_fd[2];

	if (pipe(new_fd) == -1)
		return (false);
	fd[0] = new_fd[0];
	fd[1] = new_fd[1];
	return (true);
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
int	dispatch(t_ast *ast, t_shell *shell)
{
	int	fd[3];
	int	pid;
	int	i;
	int	exit_code;
	t_intlist	*hdocs;
	int	b_id;

	hdocs = create_heredocs(ast);
	fd[1] = STDOUT_FILENO;
	fd[2] = STDIN_FILENO;
	i = 1;
	if (ast->node.type != NODE_PIPE && ast->leaf.argv)
	{
		b_id = is_builtin(ast->leaf.argv->content);
		if (b_id != -1)
			return (exec_builtin(ast, shell, &hdocs));
	}
	while (ast->node.type == NODE_PIPE)
	{
		if (!create_pipe(fd))
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (!pid)
		{
			close(fd[0]);
			child_process(ast->node.left, shell, fd, &hdocs);
		}
		close(fd[1]);
		if (fd[2] != STDIN_FILENO)
			close(fd[2]);
		fd[2] = fd[0];
		ast = ast->node.right;
		i++;
	}
	if (is_builtin(ast->leaf.argv->content) != -1)
		return (exec_builtin(ast, shell, &hdocs));
	fd[1] = STDOUT_FILENO;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child_process(ast, shell, fd, &hdocs);
	i++;
	if (fd[2] != STDIN_FILENO)
		close(fd[2]);
	set_execution_signals();
	int	status;

	while (i--)
	{
		if (wait(&status) == pid)
			exit_code = get_exit_code(status);
	}
	free(hdocs);
	return (exit_code);
}
