/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dispatcher.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:05:21 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 17:10:40 by egaziogl         ###   ########.fr       */
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

// child.c

void	child_process(t_ast *ast, t_shell *shell);
void	execute_absolute(char **argv, char **envp);
void	execute_relative(char **argv, char **envp, t_shell *shell);

// dispatch.c

int		dispatch(t_shell *shell);
void	child_process(t_ast *ast, t_shell *shell);
int		is_builtin(char *str);

// redirects.c

bool	open_file(t_shell *shell, t_redir *redir);
bool	redirect(t_ast *ast, t_shell *shell);

// expand.c

bool	expand_tokens(t_token *root, t_shell *shell);
void	expand_redirs(t_redir *root, t_shell *shell);

// expand_utils.c

char	*pick_var_name(char **str);
char	*ft_getenv(t_shell *shell, char *key);

// execute.c

bool	check_paths(char **paths);
int		exec_builtin(t_ast *ast, t_shell *shell, bool is_child);
int		builtin_sorter(int builtin_id, char **argv, t_shell *shell);

// util.c

char	**build_argv(t_token *root, int *argc);
char	**extract_paths(char *cmd, t_env *env);
int		get_exit_code(int exit_value);
int		empty_command(t_ast *ast, t_shell *shell);
int		redirect_error(t_ast *ast, t_shell *shell);

// heredoc.c

void	create_heredocs(t_shell *shell);

#endif
