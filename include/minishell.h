/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:56:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 23:37:29 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_signals.h"
# include "minishell_tokenizer.h"
# include "minishell_parser.h"
# include "minishell_builtins.h"
# include "minishell_dispatcher.h"

# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_shell
{
	t_env		*env;
	t_ast		*ast;
	t_intlist	*hdoc;
	int			fd[4];
	int			children;
	int			last_exit_status;
}	t_shell;

// shell.c

void	cleanup(t_shell *shell);
bool	parse_input(t_shell *shell, char *input);
int		init_shell(t_shell *shell, char **envp);

// prints "error: str" to stderr and exits
void	crash(char *str);
void	print_args(int argc, char **argv);
void	print_ast(t_ast *ast);

#endif
