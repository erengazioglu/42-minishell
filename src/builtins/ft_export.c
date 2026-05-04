/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:47:34 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/02 17:34:10 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static bool	ft_is_valid_export_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
			return (false);
		if (arg[i] == '=')
			return (true);
		i++;
	}
	return (true);
}

/**
 * @brief Implements the export built-in command
 * @param args Array of strings representing the command arguments
 * @param env Pointer to the environment variables list
 * @return Exit status of the command
 */
int	ft_export(char **args, t_env **env)
{
	int	i;

	if (!args || !args[0])
		return (1);
	if (ft_str_equals(args[0], "export") != 0)
		return (1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (ft_is_valid_export_arg(args[i]))
			ft_export_process_arg(args[i], env);
		else
			ft_putstr("export: invalid argument\n", 2, -1, true);
		i++;
	}
	return (0);
}
