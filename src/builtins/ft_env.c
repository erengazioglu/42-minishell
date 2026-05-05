/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:29:24 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 02:54:14 by jalfaiat         ###   ########.fr       */
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
		{
			ft_putstr(env->key, 1, -1, false);
			ft_putstr("=", 1, -1, false);
			ft_putstr(env->value, 1, -1, true);
		}
		env = env->next;
	}
	return (0);
}

t_env	*env_from_envp(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		ft_export_process_arg(envp[i], &env);
		i++;
	}
	return (env);
}

char	**env_to_envp(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*tmp_str;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	envp = ft_calloc(count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp_str = ft_strjoin(env->key, "=", -1, false);
			envp[i++] = ft_strjoin(tmp_str, env->value, -1, true);
		}
		env = env->next;
	}
	return (envp);
}
