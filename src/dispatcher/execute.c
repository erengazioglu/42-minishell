/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:48:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/06 12:24:55 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Checks if any of the given paths exist and are executable.
 * @param paths	An array of strings representing the paths to check.
 * @return	True if at least one path exists and is executable, false otherwise.
 */
bool	check_paths(char **paths)
{
	int	result;
	int	i;

	result = -1;
	i = 0;
	while (paths[i] && result)
		result &= access(paths[i++], F_OK);
	if (result == -1)
		return (free_strarr(paths), false);
	result = -1;
	i = 0;
	while (paths[i] && result)
		result &= access(paths[i++], X_OK);
	if (result == -1)
		return (free_strarr(paths), false);
	return (true);
}

int	builtin_sorter(int builtin_id, char **argv, t_env **env)
{
	if (builtin_id == CD)
		return (ft_cd(argv, env));
	if (builtin_id == ECHO)
		return (ft_echo(argv), 0);
	if (builtin_id == ENV)
		return (ft_env(argv, *env));
	if (builtin_id == EXIT)
	{
		ft_exit(argv, 0);
		return (0);
	}
	if (builtin_id == EXPORT)
		return (ft_export(argv, env));
	if (builtin_id == PWD)
		return (ft_pwd(argv));
	if (builtin_id == UNSET)
		return (ft_unset(argv, env));
	return (-1);
}

int	exec_builtin(t_ast *ast, t_env **env, t_intlist **hdoc)
{
	int		argc;
	char	**argv;
	int		builtin_id;
	int		fd[4];
	int		status;

	status = 0;
	fd[1] = STDOUT_FILENO;
	fd[2] = STDIN_FILENO;
	fd[0] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	redirect(ast, fd, hdoc);
	if (ast->leaf.argv)
		expand_tokens(ast->leaf.argv);
	argv = build_argv(ast->leaf.argv, &argc);
	if (!argv || !argv[0])
		return (free(argv), 0);
	builtin_id = is_builtin(argv[0]);
	status = builtin_sorter(builtin_id, argv, env);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	free(argv);
	return (status);
}
