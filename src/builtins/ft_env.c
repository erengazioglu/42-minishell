/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:29:24 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/02 17:35:30 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

/**
 * @brief Implements the env built-in command
 * @param args Array of strings representing the command arguments
 * @param env Pointer to the environment variables list
 * @return Exit status of the command
 */
int	ft_env(char **args, t_env *env)
{
	if (!args || !args[0])
		return (1);
	if (!ft_str_equals(args[0], "env"))
		return (1);
	if (args[1])
	{
		ft_putstr("env: too many arguments", 2, -1, true);
		return (1);
	}
	while (env)
	{
		if (env->key && env->value)
			ft_putstr(env->key, 1, -1, false), ft_putstr("=", 1, -1, false), ft_putstr(env->value, 1, -1, true);
		env = env->next;
	}
	return (0);
}
