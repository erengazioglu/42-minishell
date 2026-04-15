/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 11:47:15 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Creates a copy of a string where every character has been
 * iterated on by a given function.
 * @param s		String to iterate on.
 * @param f		Pointer to the function to be applied to each character.
 * @return	New string (memory-allocated).
 * @note	Both dst and src must be NULL-terminated.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*copy;
	int		i;

	copy = ft_strdup(s);
	if (!copy)
		return (NULL);
	i = 0;
	while (copy[i])
	{
		copy[i] = f(i, copy[i]);
		i++;
	}
	return (copy);
}
