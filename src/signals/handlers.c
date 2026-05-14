/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:42:13 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 21:43:14 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handler for SIGINT during interactive mode (when using readline).
** This moves the cursor to a new line, clears the given input and redraws.
*/
void	handle_sigint_interactive(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}
