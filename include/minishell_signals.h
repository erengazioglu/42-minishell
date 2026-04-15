/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:39:46 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/13 13:39:47 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_interactive_signals(void);
void	set_execution_signals(void);
void	set_child_signals(void);

void	rl_replace_line(const char *text, int clear_undo);

#endif
