/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strunsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:56:01 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 13:51:26 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	test_strunsplit(char **arr, char sep, int count, bool free_arr)
{
	char	*result;

	result = ft_strunsplit(arr, sep, count, free_arr);
	ft_printf("New string: %s\n", result);
	free(result);
}

int	main(int argc, char **argv)
{
	test_strunsplit(argv, ' ', argc, false);
}
