/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:53:58 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/09 19:26:48 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	crash(char *str)
{
	ft_putstr(RED, 1, -1, false);
	ft_putstr("error: ", 1, -1, false);
	ft_putstr(str, 1, -1, true);
	ft_putstr(RST, 1, -1, false);
	exit(1);
}