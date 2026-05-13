/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 02:33:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 21:52:52 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validate that all candidate paths exist and are executable.
 *
 * On failure, frees the @p paths array via free_strarr(). On success, the
 * caller keeps ownership of @p paths.
 *
 * @param paths NULL-terminated array of candidate executable paths.
 * @return true if all entries exist and are executable, false otherwise.
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

char	*ft_pathjoin(char *s1, char *s2)
{
	return (ft_strsjoin(s1, s2, '/', true));
}

char	**extract_paths(char *cmd, t_env *env)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (env)
	{
		if (ft_str_startswith(env->key, "PATH", -1))
		{
			if (!env->value || env->value[0] == '\0')
				return (NULL);
			paths = ft_split(env->value, ':', false);
			break ;
		}
		env = env->next;
	}
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_pathjoin(paths[i], cmd);
		if (!paths[i++])
			return (NULL);
	}
	return (paths);
}
