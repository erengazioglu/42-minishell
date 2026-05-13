/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:53:58 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 21:14:18 by egaziogl         ###   ########.fr       */
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
	int	exit_code;

	exit_code = 1;
	if (!msg && shell)
		exit_code = shell->last_exit_status;
	if (msg)
		ft_putstr(msg, 2, -1, true);
	if (isatty(STDIN_FILENO))
		ft_putstr("exit", 2, -1, true);
	if (shell)
		empty_shell(shell);
	rl_clear_history();
	exit(exit_code);
}

void	crash_child(int code, t_shell *shell)
{
	free_ast(shell->ast);
	empty_shell(shell);
	exit(code);
}
