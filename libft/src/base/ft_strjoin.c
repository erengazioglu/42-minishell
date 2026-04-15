/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:34:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 13:38:01 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Joins two strings together, and returns a new string as a result.
 * @param s1	String to be joined to.
 * @param s2	String to add to s1.
 * @param n		Number of characters from s1 to join to s2. If n <= 0,
 * 	uses the entire string.
 * @param free_s1	Option to free s1 at the end of the function.
 * @return	A pointer to the resulting new string.
 */
char	*ft_strjoin(char *s1, char *s2, ssize_t n, bool free_s1)
{
	char	*result;
	char	*result_base;
	char	*s1_base;

	if (n < 0 || n > (ssize_t) ft_strlen(s2))
		result = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	else
		result = ft_calloc((ft_strlen(s1) + n + 1), sizeof(char));
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
	while (*s2 && n-- != 0)
		*(result++) = *(s2++);
	*result = '\0';
	if (free_s1)
		free(s1_base);
	return (result_base);
}
