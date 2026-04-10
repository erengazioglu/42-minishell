/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:53:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 13:47:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Joins an array of strings, adding the character "sep"
 * in between each string, and returns the resulting string.
 * @param arr	Array of strings to be joined.
 * @param sep	Separating character to add between each string.
 * @param count	Number of strings to join. If count < 0, joins until it finds
 * a NULL.
 * @param free_arr	Option to free the array or not.
 * @return	A pointer to the resulting new string.
 * @note	If count < 0, the array must be NULL-terminated.
 */
char	*ft_strunsplit(char **arr, char sep, int count, bool free_arr)
{
	char	*result;
	int		i;

	result = malloc(1);
	if (!result)
		return (NULL);
	*result = 0;
	i = 0;
	while (arr[i] && count--)
	{
		if (arr[i + 1])
		{
			result = ft_strsjoin(arr[i], arr[i + 1], sep, true);
			if (!result)
			{
				if (free_arr)
					free_strarr(arr);
				return (NULL);
			}
		}
		i++;
	}
	if (free_arr)
		free_strarr(arr);
	return (result);
}
