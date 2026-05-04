/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:36:18 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/04 18:56:46 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include <stdio.h>

/**
 * @brief Implements the pwd built-in command
 * @param args Array of strings representing the command arguments
 * @return Exit status of the command
 */
int	ft_pwd(char **args)
{
	char	*path;

	if (!args || !args[0])
		return (1);
	if (!ft_str_equals(args[0], "pwd"))
		return (1);
	if (args[1])
		return (ft_putstr("pwd: too many arguments", 2, -1, true), 1);
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}
