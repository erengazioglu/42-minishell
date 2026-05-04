/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwalk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:54:05 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 23:02:08 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Walks on a string until a given `end` character, and concatenates
 * the characters read into an `acc` string (accumulator).
 * @param str	Pointer to the string to process and advance.
 * @param acc	String to concatenate to. 
 * If `NULL`, a new empty string is created.
 * @param end	Character to stop walking. 
 * If `\0`, will walk until the end.
 * @return	`acc` string (accumulator).
 */
char	*ft_strwalk(char **str, char *acc, char end)
{
	int	len;

	if (!acc)
		acc = ft_strdup("");
	len = 0;
	while ((*str)[len] && (*str)[len] != end)
		len++;
	acc = ft_strjoin(acc, ft_substr(*str, 0, len), -1, true);
	*str += len;
	return (acc);
}
