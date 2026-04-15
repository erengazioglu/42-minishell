/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:47:38 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:57:22 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Allocates memory and fills it with zero.
 * @param count	Number of members to allocate for.
 * @param size	Size of members to be allocated.
 * @return	Pointer to the memory address, or NULL if it fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			bytes;
	void			*ptr;

	if (count > SIZE_MAX / size)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	bytes = count * size;
	temp = malloc(bytes);
	if (!temp)
		return (NULL);
	ptr = (void *) temp;
	while (bytes--)
		*(temp++) = 0;
	return (ptr);
}
