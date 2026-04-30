/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static t_env	*ft_find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	ft_create_env_node(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	if (!env)
		return (1);
	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = key;
	new_node->value = value;
	if (!*env)
	{
		*env = new_node;
		return (0);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	return (0);
}

static int	ft_split_export_arg(char *arg, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(arg, '=', -1, false);
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
	}
	if (!*key || !*value)
		return (free(*key), free(*value), 1);
	return (0);
}

int	ft_export_process_arg(char *arg, t_env **env)
{
	t_env	*node;
	char	*key;
	char	*value;

	if (!env || !arg || ft_split_export_arg(arg, &key, &value))
		return (1);
	node = ft_find_env_node(*env, key);
	if (node)
	{
		free(node->value);
		node->value = value;
	}
	else if (ft_create_env_node(env, key, value))
		return (free(key), free(value), 1);
	return (0);
}
