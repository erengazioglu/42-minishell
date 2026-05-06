/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/06 12:35:51 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	child_process(t_ast *ast, t_env **env, int *fd, t_intlist **hdoc)
{
	int		argc;
	char	**argv;
	char	**paths;
	int		i;
	char	**envp;

	redirect(ast, fd, hdoc);
	expand_tokens(ast->leaf.argv);
	argv = build_argv(ast->leaf.argv, &argc);
	envp = env_to_envp(*env);
	if (ft_strchr(argv[0], '/', 0, 0))
	{
		ft_printf("Executing command: %s\n", argv[0]);
		execve(argv[0], argv, envp);
		ft_putstr("something went wrong", 2, -1, true);
		return ;
	}
	paths = extract_paths(*argv, *env);
	check_paths(paths);
	execve(argv[0], argv, envp);
	i = 0;
	while (paths && paths[i])
		execve(paths[i++], argv, envp);
	if (paths)
		free_strarr(paths);
	if (envp)
		free_strarr(envp);
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

int	dispatch(t_ast *ast, t_env **env)
{
	int	fd[3];
	int	pid;
	int	i;
	int	exit_code;
	t_intlist	*hdocs;

	hdocs = create_heredocs(ast);
	fd[1] = STDOUT_FILENO;
	fd[2] = STDIN_FILENO;
	i = 1;
	while (ast->node.type == NODE_PIPE)
	{
		if (!create_pipe(fd))
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (!pid)
			child_process(ast->node.left, env, fd, &hdocs); // TODO: child process exit if error
		close(fd[1]);
		if (fd[2] != STDIN_FILENO)
			close(fd[2]);
		fd[2] = fd[0];
		ast = ast->node.right;
		i++;
	}
	if (is_builtin(ast->leaf.argv->content) != -1)
		return (exec_builtin(ast, env, &hdocs));
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		child_process(ast, env, fd, &hdocs);
	i++;
	if (fd[2] != STDIN_FILENO)
		close(fd[2]);
	while (i--)
	{
		if (wait(&exit_code) == pid)
			exit_code = get_exit_code(exit_code);
	}
	free(hdocs);
	return (exit_code);
}
