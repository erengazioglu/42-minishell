/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endswith.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:05:31 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:27 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Checks if the end of one string matches the other.
 * @param str	String to be checked.
 * @param test	String that should match.
 * @param n		Number of characters in test string check.
 */
bool	ft_str_endswith(char *str, char *test, int n)
{
	int	len;

	len = ft_strlen(test);
	if (ft_strlen(str) < ft_strlen(test))
		return (false);
	while (*str)
		str++;
	while (*test)
		test++;
	while (len-- && n--)
	{
		if (*(--str) != *(--test))
			return (false);
	}
	return (true);
}
