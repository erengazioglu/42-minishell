/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_startswith.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:35:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 18:09:30 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Checks if the beginning of one string matches the other.
 * @param str	String to be checked.
 * @param test	String that should match.
 * @param n		Number of characters in test string check.
 * If n < 0, checks the entire test string.
 */
bool	ft_str_startswith(char *str, char *test, int n)
{
	while (*str && *test && n--)
	{
		if (*(str++) != *(test++))
			return (false);
	}
	if (*test && n)
		return (false);
	return (true);
}
