/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dispatcher.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:05:21 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 19:03:12 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DISPATCHER_H
# define MINISHELL_DISPATCHER_H

# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "minishell_parser.h"
# include "minishell_builtins.h"

# define FLAG_READ	0
# define FLAG_WRITE	1

// Forward declaration (from `minishell.h`)
typedef struct s_shell t_shell;

typedef struct s_intlist t_intlist;
struct s_intlist
{
	int	val;
	t_intlist	*next;
};

// dispatch.c

int		dispatch(t_shell *shell);
void	child_process(t_ast *ast, t_shell *shell, int *fd, t_intlist **hdoc);
int		is_builtin(char *str);

// redirects.c

bool	open_file(char *fn, t_redirtype mode, t_intlist **hdoc);
bool	redirect(t_ast *ast, int *fd, t_shell *shell, t_intlist **hdoc);

// expand.c

void	expand_tokens(t_token *root, t_shell *shell);
void	expand_redirs(t_redir *root, t_shell *shell);

// execute.c

bool	check_paths(char **paths);
int		exec_builtin(t_ast *ast, t_shell *shell, t_intlist **hdoc);
int		builtin_sorter(int builtin_id, char **argv, t_shell *shell);

// util.c

char	**build_argv(t_token *root, int *argc);
char	**extract_paths(char *cmd, t_env *env);
int		get_exit_code(int exit_value);

// heredoc.c

t_intlist	*create_heredocs(t_ast *ast);

#endif
