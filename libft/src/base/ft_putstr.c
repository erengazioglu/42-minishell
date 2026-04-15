/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:03 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/15 18:19:51 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Writes a string to a file descriptor.
 * @param s		String to write.
 * @param n		Number of characters to write. If n < 0, 
 * writes the entire string.
 * @param fd	File descriptor to write in.
 * @param newline	Option to print a '\n' after.
 * @return	Number of characters written.
 */
int	ft_putstr(char *s, int fd, int n, bool newline)
{
	int	i;

	i = 0;
	while (*s && n--)
	{
		ft_putchar(*(s++), fd, false);
		i++;
	}
	if (newline)
	{
		write(fd, "\n", 1);
		i++;
	}
	return (i);
}
