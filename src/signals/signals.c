/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:39:48 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 17:43:56 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signals.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include "minishell_globals.h"

/*
** Handler for SIGINT during interactive mode (when using readline).
** This moves the cursor to a new line, clears the given input and redraws.
*/
static void	handle_sigint_interactive(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


/**
 * @brief	Sets signals for interactive loop.
 * @note	Call this in your main loop right before calling `readline`.
 * @note	`SIGINT` (Ctrl-C): Calls our custom handler.
 * @note	`SIGQUIT` (Ctrl-\): Ignored in the shell prompt.
 */
void	set_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_interactive;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
** set_execution_signals:
** Call this in the PROMPT/PARENT PROCESS immediately when executing commands
** (e.g., right before you execute a blocking loop to wait for children).
** The parent should ignore SIGINT and SIGQUIT while a child is running.
*/
void	set_execution_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
** set_child_signals:
** Call this inside the CHILD PROCESS as the very first thing after fork().
** This resets the signals back to their default system behavior.
** If a bash command needs to exit via Ctrl-C or crash via Ctrl-\ it will do so.
*/
void	set_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
