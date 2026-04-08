/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:43:14 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 11:50:46 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Creates a copy of a slice of a given string.
 * @param s		String to slice.
 * @param start	Starting index (inclusive).
 * @param len	Number of characters to copy.
 * @return	New string (memory-allocated).
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	char	*ptr;

	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if (len == 0)
		return (ptr);
	len += start;
	temp = ptr;
	while (start < len && s[start])
	{
		*(temp++) = s[start];
		start++;
	}
	return (ptr);
}
