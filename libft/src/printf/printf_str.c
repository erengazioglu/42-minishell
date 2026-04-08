/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:46:27 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:43:55 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_printf.h"

int	printf_str(t_conv *conv, void *val)
{
	int		padding;
	int		printed;

	padding = calculate_padding_str(conv, val);
	printed = print_lpadding_str(conv, &padding);
	if (conv->flags & FLAG_PRECISION)
		printed += ft_putstr(val, 1, conv->precision, false);
	else
		printed += ft_putstr(val, 1, -1, false);
	while (padding > 0)
	{
		padding--;
		write(1, " ", 1);
		printed++;
	}
	return (printed);
}
