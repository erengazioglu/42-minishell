/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:24:00 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/07 10:47:06 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static t_env	*ft_find_env(t_env *env, char *key)
{
	while (env)
	{
		if (env->key && ft_str_equals(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static int	ft_update_env_value(t_env *node, char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return (1);
	free(node->value);
	node->value = dup;
	return (0);
}

static int	ft_create_and_append_env_node(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*tmp;

	if (!env)
		return (1);
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), 1);
	if (!*env)
		return (*env = node, 0);
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
	return (0);
}

/**
 * @brief Set or create an environment variable.
 *
 * If the key exists, replaces its value. Otherwise, appends a new node.
 *
 * @param env Environment list pointer.
 * @param key Variable name.
 * @param value Variable value.
 * @return 0 on success, non-zero on allocation/argument error.
 */
int	ft_set_env_value(t_env **env, char *key, char *value)
{
	t_env	*node;

	if (!env || !key || !value)
		return (1);
	node = ft_find_env(*env, key);
	if (node)
		return (ft_update_env_value(node, value));
	return (ft_create_and_append_env_node(env, key, value));
}

/**
 * @brief Get the previous working directory for `cd`.
 *
 * Tries getcwd() first. If that fails, falls back to the current PWD stored
 * in the environment list.
 *
 * @param env Environment list (may be NULL).
 * @return Newly allocated string, or NULL if unavailable.
 */
char	*ft_get_old_pwd(t_env *env)
{
	t_env	*node;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
		return (old_pwd);
	node = ft_find_env(env, "PWD");
	if (!node || !node->value)
		return (NULL);
	return (ft_strdup(node->value));
}
