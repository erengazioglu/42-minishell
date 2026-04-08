/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:33:17 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:11 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Fills the memory area with a constant value.
 * @param b		Pointer to the memory area.
 * @param c		Constant value to fill the memory area with.
 * @param len	The number of bytes to fill.
 * @return		A pointer to the memory area b.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *) b;
	while (len--)
		*(temp++) = (unsigned char) c;
	return (b);
}
