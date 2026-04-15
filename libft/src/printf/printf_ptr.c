/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:30:34 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:09:31 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_printf.h"

int	printf_ptr(t_conv *conv, void *val)
{
	int				zeros;
	int				padding;
	int				printed;
	unsigned long	cast;

	printed = 0;
	cast = (unsigned long) val;
	calculate_padding_int(conv, cast, &zeros, &padding);
	printed += print_lpadding_int(conv, cast, &zeros, &padding);
	if (val == NULL)
		printed += ft_putstr("(nil)", 1, -1, false);
	else
	{
		printed += ft_putstr("0x", 1, -1, false);
		printed += ft_putstr(
				ft_itoa_base(cast, "0123456789abcdef"), 1, -1, false);
	}
	printed += print_rpadding_int(conv, &padding);
	return (printed);
}
