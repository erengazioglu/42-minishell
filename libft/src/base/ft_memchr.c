/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:38:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:19:06 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Scans the memory area for a specific value.
 * @param s		Pointer to the memory area to scan.
 * @param c		Value to match.
 * @param n		Number of bytes to check.
 * @return		Pointer to the matching byte.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*((unsigned char *) s) == (unsigned char) c)
		{
			return ((void *) s);
		}
		s++;
	}
	return (NULL);
}
