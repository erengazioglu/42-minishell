/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 19:57:32 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 18:45:57 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Given an address string (separated with '/'), returns the last
 * part (e.g. /usr/bin/ls -> ls).
 * @param str	Address string.
 * @return	A pointer to the first character of filename.
 * @note	Skips double forward slashes ("//").
 */
char	*ft_get_filename(char *str)
{
	char	*retval;

	retval = str;
	while (*str)
	{
		if (*str == '/' && *(str + 1) && *(str + 1) != '/')
			retval = str + 1;
		str++;
	}
	return (retval);
}
