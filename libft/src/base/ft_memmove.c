/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:01:57 by egaziogl          #+#    #+#             */
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
 * @note	Uses a temporary array,
 * 			so it's safe to use even if memory areas overlap.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*temp;

	temp = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		dest += n - 1;
		src += n - 1;
	}
	while (n--)
	{
		if (dest > src)
			*((unsigned char *) dest--) = *((unsigned char *) src--);
		else
			*((unsigned char *) dest++) = *((unsigned char *) src++);
	}
	return (temp);
}
