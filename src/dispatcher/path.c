/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 02:33:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:34:01 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!paths[i])
			return (NULL);
		i++;
	}
	return (paths);
}
