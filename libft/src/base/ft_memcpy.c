/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:47:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:08 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Copies bytes from one memory area to another.
 * @param dest	Memory area to copy to.
 * @param src	Memory area to copy from.
 * @param n		Number of bytes to copy.
 * @return		A pointer to the memory area copied to.
 * @note	Unsafe to use if memory areas may be overlapping.
 * 			In those cases, use ft_memcpy instead.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*temp;

	if (dest == src)
		return (dest);
	temp = dest;
	while (n--)
		*((char *)dest++) = *((char *)src++);
	return (temp);
}
