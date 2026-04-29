/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:56:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/29 14:24:06 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_tokenizer.h"
# include "minishell_signals.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

// prints "error: str" to stderr and exits
void	crash(char *str);
void	print_args(int argc, char **argv);

#endif