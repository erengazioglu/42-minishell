/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:38:59 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:09:05 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Checks if the string represents a signed integer. Allows a single
 * 			'+' or '-' prefix, followed by any number.
 * @param str	String to be checked.
 */
bool	ft_str_isnum(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (false);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s)
		return (false);
	return (true);
}
