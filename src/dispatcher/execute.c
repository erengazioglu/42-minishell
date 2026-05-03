/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:48:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 17:57:20 by egaziogl         ###   ########.fr       */
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

void	execute(t_ast *ast, char **envp)
{
	(void) ast;
	(void) envp;
	// t_token	*argv;

	// argv = build_argv(ast->leaf.argv);
	// if (ft_strchr(argv->content, '/'))
	// {
	// 	execve(argv->content, state->child_args, state->envp);
	// 	crash(state, ERR_EXEC);
	// }
}