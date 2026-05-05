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
	char	cwd[1024];

	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr(cwd, 1, -1, true);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}
