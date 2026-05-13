/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:46:09 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/13 23:20:17 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

static bool	is_numeric(char *str, long long *val)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (false);
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		if (sign == 1 && res > 9223372036854775807ULL)
			return (false);
		if (sign == -1 && res > 9223372036854775808ULL)
			return (false);
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (false);
	*val = (long long)res * sign;
	return (true);
}

static void	free_exit(char **args, t_shell *shell)
{
	free(args);
	free_ast(shell->ast);
	empty_shell(shell);
	cleanup(shell);
}

/**
 * @brief Implements the exit built-in command
 * @param args Array of strings representing the command arguments
 * @param last_exit_status Last exit status of the shell.
 * @param t_shell Pointer to the shell structure.
 */
int	ft_exit(char **args, int last_status, t_shell *shell)
{
	long long	exit_code;

	ft_putstr("exit\n", 2, -1, false);
	if (args[1])
	{
		if (!is_numeric(args[1], &exit_code))
		{
			ft_putstr("minishell: exit: ", 2, -1, false);
			ft_putstr(args[1], 2, -1, false);
			ft_putstr(": numeric argument required\n", 2, -1, false);
			free_exit(args, shell);
			exit(2);
		}
		if (args[2])
		{
			ft_putstr("minishell: exit: too many arguments\n", 2, -1, false);
			return (1);
		}
	}
	else
		exit_code = last_status;
	free_exit(args, shell);
	exit(exit_code % 256);
}
