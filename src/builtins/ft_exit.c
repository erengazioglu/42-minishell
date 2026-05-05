/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:46:09 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 16:43:38 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static	bool	is_numeric(char *str)
{
	if (!str || !str[0])
		return (false);
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/**
 * @brief Implements the exit built-in command
 * @param args Array of strings representing the command arguments
 * @param last_exit_status Last exit status of the shell.
 */
void	ft_exit(char **args, int last_exit_status)
{
	ft_putstr("exit", 1, -1, true);
	if (args[1] && is_numeric(args[1]))
	{
		if (args[2])
			ft_putstr("exit: too many arguments", 2, -1, true);
		else
		{
			exit(ft_atoi(args[1]));
		}
	}
	else if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr("minishell: exit: ", 2, -1, false);
		ft_putstr(args[1], 2, -1, false);
		ft_putstr(": numeric argument required", 2, -1, true);
		exit(255);
	}
	else
	{
		exit(last_exit_status);
	}
}
