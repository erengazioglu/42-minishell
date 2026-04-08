/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:03 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 15:40:59 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Writes a string to a file descriptor.
 * @param n		String to write.
 * @param fd	File descriptor to write in.
 * @param newline	Option to print a '\n' after.
 * @return	Number of characters written.
 * @note	If n < 0, writes the entire string.
 */
int	ft_putstr(char *s, int fd, int n, bool newline)
{
	int	i;

	i = 0;
	while (*s && n--)
		ft_putchar(s++[i++], fd, false);
	if (newline)
	{
		write(fd, "\n", 1);
		i++;
	}
	return (i);
}
