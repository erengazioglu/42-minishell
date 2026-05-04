/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dispatcher.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:05:21 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/04 18:03:38 by egaziogl         ###   ########.fr       */
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

# define FLAG_READ	0
# define FLAG_WRITE	1

// dispatch.c

int		dispatch(t_ast *ast, char **envp);

// redirects.c

bool	open_file(char *fn, t_redirtype mode);
void	redirect(t_ast *ast, int *fd);

// expand.c

void	expand_tokens(t_token *root);
void	expand_redirs(t_redir *root);

// execute.c

bool	check_paths(char **paths);
int		exec_builtin(t_ast *ast, char **envp);

// util.c

char	**build_argv(t_token *root, int *argc);
char	**extract_paths(char *cmd, char **envp);
int		get_exit_code(int exit_value);

#endif