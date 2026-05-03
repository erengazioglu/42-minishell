/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:54:45 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 11:45:02 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Joins two strings together, with a character in between,
 * 			and returns a new string as a result.
 * @param s1		String to be joined to.
 * @param s2		String to join to s1.
 * @param sep		Character to be placed between s1 and s2.
 * @param free_s1	Option to free s1 at the end of the function.
 * @return	A pointer to the resulting new string.
 */
char	*ft_strsjoin(char *s1, char *s2, char sep, bool free_s1)
{
	char	*result;
	char	*result_base;
	char	*s1_base;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
	{
		if (free_s1)
			free(s1);
		return (NULL);
	}
	result_base = result;
	s1_base = s1;
	while (*s1)
		*(result++) = *(s1++);
	*(result++) = sep;
	while (*s2)
		*(result++) = *(s2++);
	*result = '\0';
	if (free_s1)
		free(s1_base);
	return (result_base);
}
