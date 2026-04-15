/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:41:15 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 13:28:31 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	count_chars(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	copy_digits(int n, char *s, int len)
{
	if (n < 0)
	{
		*s = '-';
		n *= -1;
	}
	s += len - 1;
	while (n)
	{
		*(s--) = '0' + (n % 10);
		n /= 10;
	}
}

/**
 * @brief	Parses the given integer into a new, memory-allocated string
 * (in base 10).
 * @param n	Integer to be parsed.
 * @return	The resulting string, or NULL if there's a malloc error.
 */
char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = count_chars(n);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (n == 0)
		*result = '0';
	else if (n == -2147483648)
		ft_strlcpy(result, "-2147483648", 12);
	else
		copy_digits(n, result, len);
	return (result);
}
