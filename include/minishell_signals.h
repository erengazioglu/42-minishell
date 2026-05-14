/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:39:46 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/14 21:49:07 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include <signal.h>

void	set_interactive_signals(void);
void	set_execution_signals(void);
void	set_child_signals(void);
void	set_heredoc_signals(void);
void	rl_replace_line(const char *text, int clear_undo);
void	handle_sigint_interactive(int signum);
void	handle_sigint_heredoc(int signum);

#endif
