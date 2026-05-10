/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:30:30 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/10 13:30:31 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	print_split(char **arr)
{
	int	i;

	if (!arr)
	{
		ft_printf("(null)\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		ft_printf("[%d] %s\n", i, arr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**split;

	if (argc != 2)
	{
		ft_printf("Usage: ./test_split_quotes '<input>'\n");
		return (1);
	}
	split = ft_split_quotes(argv[1]);
	if (!split)
	{
		ft_printf("Error: unmatched quotes or allocation failure\n");
		return (1);
	}
	print_split(split);
	free_strarr(split);
	return (0);
}
