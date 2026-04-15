/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:29:06 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 19:04:25 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Concatenates one NULL-terminated string to the end of another.
 * @param dst	String to receive the concatenation.
 * @param src	String to be added to the end of dst.
 * @note	The strings must be NULL-terminated.
 */
void	ft_strcat(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
		*(dst++) = *(src++);
	*dst = 0;
}
