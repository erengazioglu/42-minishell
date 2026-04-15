/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:26:00 by egaziogl          #+#    #+#             */
/*   Updated: 2025/12/12 17:13:50 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include "libft_base.h"
# include <stdarg.h>

# define FLAG_LJUSTIFY	0x01
# define FLAG_ZEROPAD	0x02
# define FLAG_PRECISION	0x04
# define FLAG_SIGN		0x08
# define FLAG_SPACE		0x10
# define FLAG_ALTERNATE	0x20

typedef unsigned int	t_flags;

typedef struct s_conv
{
	t_flags			flags;
	char			specifier;
	unsigned int	precision;
	unsigned int	width;
}	t_conv;

// padding

void	calculate_padding_int(t_conv *conv, int val, int *zeros, int *padding);
int		print_lpadding_int(t_conv *conv, int val, int *zeros, int *padding);
int		print_rpadding_int(t_conv *conv, int *padding);
int		calculate_padding_str(t_conv *conv, char *val);
int		print_lpadding_str(t_conv *conv, int *padding);
int		print_rpadding_str(t_conv *conv, int *padding);

// parsing & printing

int		ft_printf(const char *fstr, ...);
t_conv	*parse_conv(const char **str);
int		printf_char(t_conv *conv, char val);
int		printf_str(t_conv *conv, void *val);
int		printf_ptr(t_conv *conv, void *val);
int		printf_int(t_conv *conv, int val);
int		printf_uint(t_conv *conv, unsigned int val);
int		printf_hex(t_conv *conv, unsigned int val);
int		printf_percent(void);

#endif