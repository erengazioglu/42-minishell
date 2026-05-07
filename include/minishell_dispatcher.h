/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dispatcher.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:05:21 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 13:05:27 by jalfaiat         ###   ########.fr       */
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

// dispatch.c

int		dispatch(t_ast *ast, t_shell *shell);
void	child_process(t_ast *ast, t_shell *shell, int *fd);
int		is_builtin(char *str);

// redirects.c

bool	open_file(char *fn, t_redirtype mode);
bool	redirect(t_ast *ast, int *fd, t_shell *shell);

// expand.c

void	expand_tokens(t_token *root, t_shell *shell);
void	expand_redirs(t_redir *root, t_shell *shell);

// execute.c

bool	check_paths(char **paths);
int		exec_builtin(t_ast *ast, t_shell *shell);
int		builtin_sorter(int builtin_id, char **argv, t_shell *shell);

// util.c

char	**build_argv(t_token *root, int *argc);
char	**extract_paths(char *cmd, t_env *env);
int		get_exit_code(int exit_value);

#endif
