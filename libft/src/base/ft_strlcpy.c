/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 23:50:12 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 11:36:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Copies a string to another, and always NULL-terminates.
 * @param dst	String to overwrite.
 * @param src	String to be copied.
 * @param dstsize	Size of dst. (at most dstsize-1 characters will be copied)
 * @return	Length of src. If retval >= siz, truncation has occurred.
 * @note	Only src needs to be NULL-terminated.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	while (src[i])
	{
		if (dstsize > 1)
		{
			*(dst++) = src[i];
			dstsize--;
		}
		i++;
	}
	*dst = 0;
	return (i);
}
