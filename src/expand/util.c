/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:36:38 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 01:10:12 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Slices a portion of the string, returns the slice,
 * and updates the string pointer to the remaining part.
 * @param str Pointer to the original string. It will be freed and replaced
 * by the remaining part after slicing.
 * @param start Starting index of the slice.
 * @param len Length of the slice.
 * @return Newly allocated slice of the string, or NULL on failure.
 * @note Handles the memory management. You insert 1 memory-allocated string,
 * get 1 memory-allocated slice, and the original string is updated.
 */
char *ft_strslice(char **str, int start, int len)
{
	char	*slice;
	char	*src;

	if (!str)
		return (NULL);
	slice = ft_substr(*str, start, len);
	if (!slice)
		return (NULL);
	src = *str;
	*str = ft_strdup(src + start + len);
	free(src);
	return (slice);
}
