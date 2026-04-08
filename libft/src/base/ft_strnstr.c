/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:36:35 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 18:39:51 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Finds a string of characters (needle) in another (haystack),
 * and returns a pointer to the first occurrence.
 * @param haystack	String to be checked.
 * @param needle	Substring to look for.
 * @param len		Number of characters to search.
 * @return	A pointer to the first character of the first matching string.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (!(*needle))
		return ((char *) haystack);
	if (!len)
		return (NULL);
	needle_len = ft_strlen(needle);
	while (*haystack && len-- >= needle_len)
	{
		if (*haystack == *needle)
			if (!ft_strncmp(haystack, needle, ft_strlen(needle)))
				return ((char *) haystack);
		haystack++;
	}
	return (NULL);
}
