/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:07:40 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/04 18:56:52 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static bool	ft_is_valid_unset_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_remove_env_variable(char *arg, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_str_equals(tmp->key, arg))
		{
			if (tmp->prev == NULL)
				*env = tmp->next;
			else
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

/**
 * @brief Implements the unset built-in command
 * @param args Array of strings representing the command arguments
 * @param env Pointer to the environment variables list
 * @return Exit status of the command
 */
int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (!args || !args[0])
		return (1);
	if (!ft_str_equals(args[0], "unset"))
		return (1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (ft_is_valid_unset_arg(args[i]))
			ft_remove_env_variable(args[i], env);
		else
			ft_putstr("unset: invalid argument", 2, -1, true);
		i++;
	}
	return (0);
}
