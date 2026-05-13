/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:29:24 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/13 22:13:18 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

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
		ft_putstr("env: '", 2, -1, false);
		ft_putstr(args[1], 2, -1, false);
		ft_putstr("': No such file or directory", 2, -1, true);
		return (127);
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

/**
 * @brief Build an internal env list from a traditional envp array.
 *
 * Each entry is processed via export parsing logic.
 *
 * @param envp NULL-terminated array of "KEY=VALUE" strings.
 * @return Head of a newly allocated env list (may be NULL).
 */
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

char	**create_empty_envp(t_env *env)
{
	int		len;

	len = 0;
	while (env)
	{
		if (env->value)
			len++;
		env = env->next;
	}
	return (ft_calloc(len + 1, sizeof(char *)));
}

/**
 * @brief Convert an internal env list into an envp array.
 *
 * Only nodes with a non-NULL value are included.
 *
 * @param env Head of env list.
 * @return Newly allocated NULL-terminated array, or NULL on allocation error.
 */
char	**env_to_envp(t_env *env)
{
	int		i;
	char	*temp;
	char	**envp;

	envp = create_empty_envp(env);
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			temp = ft_strjoin(env->key, "=", -1, false);
			envp[i++] = ft_strjoin(temp, env->value, -1, true);
		}
		env = env->next;
	}
	return (envp);
}
