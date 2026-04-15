/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:41:41 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/05 21:45:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft_base.h"

/**
 * @brief Writes a character to a file descriptor.
 * @param char	Character to write.
 * @param fd	File descriptor to write in.
 * @param newline	Option to print a '\n' after.
 */
void	ft_putchar(char c, int fd, bool newline)
{
	write(fd, &c, 1);
	if (newline)
		write(fd, "\n", 1);
}
