/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:56:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/15 18:15:40 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_tokenizer.h"
# include "minishell_signals.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <string.h>

// prints "error: str" to stderr and exits
void	crash(char *str);
void	print_args(int argc, char **argv);

#endif