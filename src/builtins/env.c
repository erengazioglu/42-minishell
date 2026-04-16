/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:29:24 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/16 19:47:43 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **args, t_env *env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "env") != 0)
		return (1);
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (127);
	}
	while (env)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
