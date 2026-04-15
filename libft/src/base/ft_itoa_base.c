/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:53:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 13:31:17 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "limits.h"

static int	count_chars(unsigned long n, char *base)
{
	int	count;
	int	len;

	if (!n)
		return (1);
	count = 0;
	len = ft_strlen(base);
	while (n)
	{
		n /= len;
		count++;
	}
	return (count);
}

static void	copy_digits(unsigned long n, char *s, int len, char *base)
{
	int	base_len;

	base_len = ft_strlen(base);
	s += len - 1;
	while (n)
	{
		*(s--) = base[n % base_len];
		n /= base_len;
	}
}

/**
 * @brief	Parses the given integer into a new, memory-allocated string
 * (in a custom base, represented by a string of unique characters).
 * @param n		Integer to be parsed.
 * @param base	Set of unique characters representing the base.
 * @return	The resulting string, or NULL if there's a malloc error.
 */
char	*ft_itoa_base(unsigned long n, char *base)
{
	char	*result;
	int		len;

	len = count_chars(n, base);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (n == 0)
		*result = '0';
	else
		copy_digits(n, result, len, base);
	return (result);
}
