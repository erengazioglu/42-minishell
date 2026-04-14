/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 23:19:32 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/14 13:53:10 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <stdio.h>
#include <stdbool.h>

static bool	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

void	ft_echo(char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	if (!args || !args[0])
		return ;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
