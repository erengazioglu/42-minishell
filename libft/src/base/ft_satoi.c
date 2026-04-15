/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:41:47 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:08:49 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

static int	init_satoi(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

static int	case_intmin(const char *str)
{
	if (str[11])
	{
		if (ft_isdigit(str[11]))
			return (errno = ERANGE, 0);
		return (errno = EINVAL, 0);
	}
	return (-2147483648);
}

/**
 * @brief	Converts the given string into an integer, enforcing a properly
 * formatted string representing an integer. Allows a single '-' or '+' prefix.
 * @return	The resulting integer, or 0 if there's an error.
 * @note	Sets `errno` to `EINVAL` if string does not accurately represent 
 * a number, or `ERANGE` if the number is < `INT_MIN` or > `INT_MAX`.
 */
int	ft_satoi(const char *str)
{
	int	acc;
	int	sign;
	int	digit;

	if (!ft_strncmp(str, "-2147483648", 11))
		return (case_intmin(str));
	if (!(*str))
		return (errno = EINVAL, 0);
	sign = init_satoi(&str);
	if (!(*str))
		return (errno = EINVAL, 0);
	acc = 0;
	while (ft_isdigit(*str))
	{
		digit = *(str++) - '0';
		if (acc > (2147483647 - digit) / 10)
			return (errno = ERANGE, 0);
		acc = acc * 10 + digit;
	}
	if (*str)
		return (errno = EINVAL, 0);
	return (sign * acc);
}
