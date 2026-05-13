/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:53:58 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:19:34 by egaziogl         ###   ########.fr       */
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

void	crash_main(char *msg, t_shell *shell)
{
	if (msg)
		ft_putstr(msg, 2, -1, true);
	if (isatty(STDIN_FILENO))
		ft_putstr("exit", 2, -1, true);
	if (shell)
		empty_shell(shell);
	rl_clear_history();
	exit(1);
}
