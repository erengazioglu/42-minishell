/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:53:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/09 19:07:11 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Joins a NULL-terminated array of strings, adding the character "sep"
 * in between each string, and returns the resulting string.
 * @param arr	Array of strings to be joined (has to be NULL-terminated).
 * @param sep	Separating character to add between each string.
 * @param free_arr	Option to free the array or not.
 * @return	A pointer to the resulting new string.
 */
char	*ft_strunsplit(char **arr, char sep, bool free_arr)
{
	char	*result;

	result = "";
	while (*arr)
	{
		if (*(arr + 1))
			result = ft_strsjoin(*arr, *(arr + 1), sep, true);
		arr++;
	}
	if (free_arr)
		free_strarr(arr);
	return (result);
}
