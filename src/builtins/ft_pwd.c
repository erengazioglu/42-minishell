/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:36:18 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/19 21:30:51 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

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
	if (ft_strcmp(args[0], "pwd") != 0)
		return (1);
	if (args[1])
		return (ft_putstr_fd("pwd: too many arguments\n", 2), 1);
	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}
