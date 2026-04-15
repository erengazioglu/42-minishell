/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:36:53 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/12 19:16:42 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Calculates the length of a null-terminated string.
 * @param s		String to check.
 * @return		Number of characters up to the first null character.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (-1);
	len = 0;
	while (*(s++))
		len++;
	return (len);
}
