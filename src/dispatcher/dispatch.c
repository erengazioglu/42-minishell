/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/04 18:11:17 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *str)
{
	return (
		ft_str_equals(str, "cd")
		|| ft_str_equals(str, "echo")
		|| ft_str_equals(str, "env")
		|| ft_str_equals(str, "export")
		|| ft_str_equals(str, "pwd")
		|| ft_str_equals(str, "unset")
		|| ft_str_equals(str, "exit")
	);
}

void	child_process(t_ast *ast, char **envp, int *fd)
{
	int		argc;
	char	**argv;
	char	**paths;
	int		i;

	redirect(ast, fd);
	expand_tokens(ast->leaf.argv);
	argv = build_argv(ast->leaf.argv, &argc);
	if (ft_strchr(argv[0], '/', 0, 0))
	{
		ft_printf("Executing command: %s\n", argv[0]);
		execve(argv[0], argv, envp);
		ft_putstr("something went wrong", 2, -1, true);
		return ;
	}
	paths = extract_paths(*argv, envp);
	check_paths(paths);
	execve(argv[0], argv, envp);
	i = 0;
	while (paths[i])
		execve(paths[i++], argv, envp);
	free_strarr(paths);
	ft_putstr("something went wrong", 2, -1, true);
}

// returns false if it fails
bool	create_pipe(int *fd)
{
	int	new_fd[2];

	if (pipe(new_fd) == -1)
		return (false);
	fd[0] = new_fd[0];
	fd[1] = new_fd[1];
	return (true);
}

int	dispatch(t_ast *ast, char **envp)
{
	int	fd[3];
	int	pid;
	int	i;
	int	exit_code;

	fd[1] = STDOUT_FILENO;
	fd[2] = STDIN_FILENO;
	i = 1;
	while (ast->node.type == NODE_PIPE)
	{
		if (!create_pipe(fd))
			return (-1); // TODO: error while creating pipe
		pid = fork();
		if (pid == -1)
			return (-1); // TODO: error while forking
		if (!pid)
			child_process(ast->node.left, envp, fd); // TODO: child process exit if error
		close(fd[1]);
		if (fd[2] != STDIN_FILENO)
			close(fd[2]);
		fd[2] = fd[0];
		ast = ast->node.right;
		i++;
	}
	if (is_builtin(ast->leaf.argv->content))
		return (exec_builtin(ast, envp));
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child_process(ast, envp, fd);
	i++;
	if (fd[2] != STDIN_FILENO)
		close(fd[2]);
	while (i--)
	{
		if (wait(&exit_code) == pid)
			exit_code = get_exit_code(exit_code);
	}
	return (exit_code);
}

/*

ls | cat -e | cat -e

PIPE() -> pipe1[0], pipe1[1]
ls  - STDIN ; PIPE1[1]
PIPE() -> pipe2[0], pipe2[1]
cat - PIPE1[0] ; PIPE2[1];
cat2- PIPE2[0] ; STDOUT


*/