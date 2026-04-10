/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:53:19 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 17:03:16 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

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

	if (!count)
		return (NULL);
	result = ft_strdup(*arr);
	if (!result)
		return (NULL);
	// ft_printf("running strunsplit\nfirst:\"%s\", sep:%c, count:%d, free:%d\n",
		result, sep, count, free_arr);
	i = 1;
	while (arr[i] && --count)
	{
		// ft_printf("joining \"%s\" and \"%s\"\n", result, arr[i]);
		result = ft_strsjoin(result, arr[i++], sep, true);
		// ft_printf("result:%s\n", result);
		if (!result)
		{
			if (free_arr)
				free_strarr(arr);
			return (NULL);
		}
	}
	if (free_arr)
		free_strarr(arr);
	return (result);
}
