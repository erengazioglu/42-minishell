/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:52:26 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 18:22:31 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

void	test_strchr(const char *s, char c, int n, bool reverse)
{
	char	*result;

	result = ft_strchr(s, c, n, reverse);
	printf("look for %c in %s\n", c, s);
	printf("n=%d, reverse=%d\n", n, reverse);
	printf("%s\n---\n\n", result);
}

int	main(void)
{
	test_strchr("hello", 'h', 0, false);
	test_strchr("hello", 'h', 1, false);
	test_strchr("hello", 'h', 5, false);
	test_strchr("hello", 'h', 7, false);
	test_strchr("hello", 'l', 0, true);
	test_strchr("hello", 'l', 1, true);
	test_strchr("hello", 'l', 5, true);
	test_strchr("hello", 'l', 5, false);
}
