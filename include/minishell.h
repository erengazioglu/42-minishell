/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:56:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 18:24:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_signals.h"
# include "minishell_tokenizer.h"
# include "minishell_parser.h"
# include "minishell_builtins.h"
# include "minishell_dispatcher.h"
# include "minishell_shell.h"
# include "minishell_expand.h"

# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>

// crash.c 

void	crash(char *str);
void	crash_main(char *str, t_shell *shell);
void	crash_child(int code, t_shell *shell);
void	print_args(int argc, char **argv);
void	print_ast(t_ast *ast);

#endif
