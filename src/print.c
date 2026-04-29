/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:54:40 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/29 15:44:51 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_args(int argc, char **argv)
{
	int	i;

	i = 1;
	ft_printf("%s%d args:\n(0) %s", YEL, argc, argv[0]);
	while (i < argc)
	{
		ft_printf("\n(%d) %s", i, argv[i]);
		i++;
	}
	ft_printf("%s\n", RST);
}
