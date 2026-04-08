/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:21:36 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/05 21:48:17 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Checks if a character represents an alphanumeric value.
 * @param c		Character to check.
 */
bool	ft_isalnum(int c)
{
	if
	(
		(c <= '9' && c >= '0') ||
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z')
	)
		return (1);
	return (0);
}
