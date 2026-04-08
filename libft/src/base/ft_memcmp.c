/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:06:17 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:07 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Compares bytes from two memory areas.
 * @param s1	Memory area to compare.
 * @param s2	Other memory area to compare.
 * @param n		Number of bytes to compare.
 * @return		The difference between the first pair of bytes that differ.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	int				diff;

	temp1 = (unsigned char *) s1;
	temp2 = (unsigned char *) s2;
	while (n--)
	{
		diff = *(temp1++) - *(temp2++);
		if (diff)
			return (diff);
	}
	return (0);
}
