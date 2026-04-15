/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:43:05 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:08:25 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

static char	check_rest(char const *str, char const *set)
{
	while (*str)
		if (!ft_strchr(set, *(str++), 0, false))
			return (0);
	return (1);
}

/**
 * @brief	Creates a copy of the string where a set of characters are removed
 * from both ends.
 * @param s1	String to trim.
 * @param set	Characters to remove from the string.
 * @return	A new string with both ends trimmed.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*temp;

	temp = (char *) s1;
	start = 0;
	len = 0;
	while (*temp && ft_strchr(set, *temp, 0, false))
	{
		start++;
		temp++;
	}
	while (*temp && !check_rest(temp, set))
	{
		len++;
		temp++;
	}
	return (ft_substr(s1, start, len));
}
