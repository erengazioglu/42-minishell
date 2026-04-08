/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:16:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:44:44 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_printf.h"

int	printf_int(t_conv *conv, int val)
{
	int		zeros;
	int		padding;
	int		printed;
	char	*str;

	printed = 0;
	calculate_padding_int(conv, val, &zeros, &padding);
	printed += print_lpadding_int(conv, val, &zeros, &padding);
	if (val == -2147483648)
		printed += ft_putstr("2147483648", 1, -1, false);
	else if (
		!(val == 0 && conv->flags & FLAG_PRECISION && conv->precision == 0)
	)
	{
		if (val < 1)
			val *= -1;
		str = ft_itoa(val);
		if (!str)
			return (-1);
		printed += ft_putstr(str, 1, -1, false);
		free(str);
	}
	printed += print_rpadding_int(conv, &padding);
	return (printed);
}
