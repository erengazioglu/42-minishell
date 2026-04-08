/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:41:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:58:13 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Writes an integer to a file descriptor.
 * @param n		Integer to write.
 * @param fd	File descriptor to write in.
 * @param newline	Option to print a '\n' after.
 */
void	ft_putnbr(int n, int fd, bool newline)
{
	char	c;

	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr(-n, fd, false);
	}
	else
	{
		if (n / 10)
			ft_putnbr(n / 10, fd, false);
		c = '0' + (n % 10);
		write(fd, &c, 1);
	}
	if (newline)
		write(fd, "\n", 1);
}
