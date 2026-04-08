/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:58:34 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:46 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Compare n characters of two strings.
 * @param s1	First string.
 * @param s2	Second string.
 * @param n		Number of characters to compare.
 * @return		0 if equal, 
 * difference between the first matching characters otherwise.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	while (n > 1 && *s1 && *s2)
	{
		c1 = (unsigned char) *s1;
		c2 = (unsigned char) *s2;
		if (*s1 != *s2)
			return (c1 - c2);
		s1++;
		s2++;
		n--;
	}
	c1 = (unsigned char) *s1;
	c2 = (unsigned char) *s2;
	return (c1 - c2);
}
