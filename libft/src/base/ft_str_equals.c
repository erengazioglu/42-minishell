/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_equals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:12:03 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:18:29 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Checks if the one string matches the other.
 * @param str	String to be checked.
 * @param test	String that should match.
 */
bool	ft_str_equals(char *str, char *test)
{
	while (*str && *test)
	{
		if (*(str++) != *(test++))
			return (false);
	}
	if (*test || *str)
		return (false);
	return (true);
}
