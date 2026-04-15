/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:47:02 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 11:38:45 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Copies a string to the end of another, and always NULL-terminates.
 * @param dst	String to concatenate to.
 * @param src	String to be joined.
 * @param dstsize	Size of dst. (at most dstsize-1 characters will be copied)
 * @return	Length of src. If retval >= siz, truncation has occurred.
 * @note	Both dst and src must be NULL-terminated.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	if (!dstsize)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (len > dstsize)
		len = dstsize;
	len += ft_strlen(src);
	while (*dst)
	{
		if (dstsize)
			dstsize--;
		dst++;
	}
	while (*src)
	{
		if (dstsize > 1)
		{
			*(dst++) = *src;
			dstsize--;
		}
		src++;
	}
	*dst = 0;
	return (len);
}
