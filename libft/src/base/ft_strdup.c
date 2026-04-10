/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:24:02 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 14:43:42 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Creates a memory-allocated copy of the string.
 * @param s	String to clone.
 * @return	New string.
 */
char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*temp;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	temp = ft_calloc((len + 1), sizeof(char));
	if (!temp)
		return (NULL);
	ptr = temp;
	while (len--)
		*(temp++) = *(s++);
	return (ptr);
}
