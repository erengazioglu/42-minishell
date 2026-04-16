/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:46:09 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/16 18:08:33 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool is_numeric(char *str)
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

void ft_exit(char **args)
{
	
}
