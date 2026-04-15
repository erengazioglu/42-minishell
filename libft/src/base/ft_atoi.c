/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:20:54 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 13:09:58 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief	Converts the given string into an integer.
 * @return	The resulting integer.
 * @note	Atoi trims whitespace, allows one '-' or '+' prefix,
 * and any number of digits adding up to INT_MIN or INT_MAX. It will parse
 * until it finds an invalid character, and return the result 
 * up to that point. Use `ft_satoi` for more strict rules and error handling.
 */
int	ft_atoi(const char *str)
{
	int	acc;
	int	sign;

	if (!(*str))
		return (0);
	sign = 1;
	acc = 0;
	if (!ft_strncmp(str, "-2147483647", 11))
		return (-2147483647);
	while (ft_strchr("\t\v\f\r\n ", *str, 0, 0))
		str++;
	if (ft_strchr("-+", *str, 0, 0))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (sign * acc);
		acc = acc * 10 + (*(str++) - '0');
	}
	return (sign * acc);
}
