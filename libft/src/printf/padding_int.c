/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:31:07 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:59:06 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_printf.h"

static int	count_chars(int n, int base)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= base;
		count++;
	}
	return (count);
}

void	calculate_padding_int(t_conv *conv, int val, int *zeros, int *padding)
{
	unsigned int	char_count;

	if (ft_strchr("xXp", conv->specifier, 0, 0))
		char_count = count_chars(val, 16);
	else
		char_count = count_chars(val, 10);
	*zeros = 0;
	*padding = conv->width - char_count - (val < 0);
	if (conv->flags & (FLAG_ZEROPAD | FLAG_PRECISION))
	{
		if (conv->flags & FLAG_PRECISION)
		{
			*zeros = conv->precision - char_count;
			*padding = ft_min(*padding, conv->width - conv->precision);
			if (conv->flags & FLAG_ZEROPAD || conv->precision > char_count)
				*padding -= (val < 0);
		}
		else
		{
			*zeros = *padding;
			*padding = 0;
		}
	}
}

int	print_lpadding_int(t_conv *conv, int val, int *zeros, int *padding)
{
	int	printed;

	printed = 0;
	if (val == 0 && (conv->flags & FLAG_PRECISION) && conv->precision == 0)
	{
		if (!(conv->flags & FLAG_LJUSTIFY))
			*padding = 0;
		return (0);
	}
	if (!(conv->flags & FLAG_LJUSTIFY))
	{
		while ((*padding)-- > 0)
			printed += ft_putstr(" ", 1, 1, false);
	}
	if (!ft_strchr("xXpu", conv->specifier, 0, 0))
	{
		if (val < 0)
			printed += ft_putstr("-", 1, 1, false);
		else if (conv->flags & FLAG_SIGN)
			printed += ft_putstr("+", 1, 1, false);
	}
	while ((*zeros)-- > 0)
		printed += ft_putstr("0", 1, 1, false);
	return (printed);
}

int	print_rpadding_int(t_conv *conv, int *padding)
{
	int	printed;

	printed = 0;
	if (conv->flags & FLAG_LJUSTIFY)
	{
		while ((*padding)-- > 0)
			printed += ft_putstr(" ", 1, 1, false);
	}
	return (printed);
}
