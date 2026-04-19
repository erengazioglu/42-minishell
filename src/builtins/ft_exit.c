/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:46:09 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/19 21:19:40 by jalfaiat         ###   ########.fr       */
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
	ft_putstr_fd("exit\n", 1);
	if (args[1] && is_numeric(args[1]))
	{
		if (args[2])
			ft_putstr_fd("exit: too many arguments\n", 2);
		else
		{
			ft_free_all();
			exit(ft_atoi(args[1]));
		}
	}
	else if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_all();
		exit(255);
	}
	else
	{
		ft_free_all();
		exit(last_exit_status);
	}
}
