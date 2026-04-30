/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:07:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 11:40:09 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Finds a specific value in a string, and returns a pointer to the
 * first occurrence.
 * @param s	String to be checked.
 * @param c	Character to find.
 * @param n	Number of characters to check. If <= 0, checks the entire string.
 * @param reverse	If true, start checking from the end.
 * @return	A pointer to the first matching character.
 * @note	To get the index of first match instead, use ft_strfind.
 */
char	*ft_strchr(const char *s, char c, int n, bool reverse)
{
	int	dir;
	int	len;

	len = ft_strlen(s);
	if (n >= len || n <= 0)
		n = len;
	if (!c && ((reverse && n) || n >= len - 1))
		return ((char *) &s[len]);
	dir = -reverse | 1;
	if (reverse)
		s += len - 1;
	while (*s && n--)
	{
		if (*s == c)
			return ((char *) s);
		s += dir;
	}
	return (NULL);
}
