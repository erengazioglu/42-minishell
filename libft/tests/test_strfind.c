/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 23:56:01 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:10:10 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

void	test_strfind(char *s, char c, int n, bool reverse)
{
	printf("look for %c in %s\n", c, s);
	printf("n=%d, reverse=%d\n", n, reverse);
	printf("%d\n---\n\n", ft_strfind(s, c, n, reverse));
}

int	main(void)
{
	test_strfind("hello", 'h', 0, false);
	test_strfind("hello", 'h', 1, false);
	test_strfind("hello", 'h', 5, false);
	test_strfind("hello", 'h', 7, false);
	test_strfind("hello", 'l', 0, true);
	test_strfind("hello", 'l', 1, true);
	test_strfind("hello", 'l', 5, true);
	test_strfind("hello", 'l', 7, true);
}
