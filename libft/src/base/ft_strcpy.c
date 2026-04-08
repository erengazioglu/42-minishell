/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:37:42 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:53:55 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Copies the content of src over dst, overwriting it up to a specific
 * delimiter, and returns a pointer at the end of dst.
 * @param dst		String to be overwritten.
 * @param src		String to be copied.
 * @param delim		Character in "src" that will stop the copying operation.
 * 	Use \0 if you want to copy the entire null-terminated string.
 * @param end		Character to append at the end of the operation.
 * 	Use \0 if you don't want anything (usual behavior).
 * @return	A pointer to the null character at the end of the operation.
 * @note	This is particularly useful when building long strings,
 * because you can assign the return value to a cursor and loop until you've
 * built the full string.
 */
char	*ft_strcpy(char *dst, char *src, char delim, char end)
{
	while (*src != delim)
		*dst++ = *src++;
	if (end)
		*dst++ = end;
	*dst = '\0';
	return (dst);
}
