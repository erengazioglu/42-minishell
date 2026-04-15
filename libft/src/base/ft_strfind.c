/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:18:45 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 18:28:13 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Finds a specific value in a string, and returns the index of the
 * first occurrence.
 * @param s	String to be checked.
 * @param c	Character to find.
 * @param n	Number of characters to check. If <= 0, will use the entire string.
 * @param reverse	If true, start checking from the end.
 * @return	The index of the first matching character.
 * @note	To get a pointer to the first match instead, use ft_strchr.
 * 			Prefer ft_strchr when only checking if value exists, 
 * 			since it returns a NULL if it's not found.
 */
int	ft_strfind(const char *s, char c, int n, bool reverse)
{
	int	i;
	int	dir;
	int	len;

	len = ft_strlen(s);
	if (n >= len || n <= 0)
		n = len - 1;
	dir = -reverse | 1;
	i = 0;
	if (reverse)
		i = len - 1;
	while (s[i] && n--)
	{
		if (s[i] == c)
			return (i);
		i += dir;
	}
	return (-1);
}
