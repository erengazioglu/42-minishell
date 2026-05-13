/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 02:08:15 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:52:21 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SHELL_H
# define MINISHELL_SHELL_H

# include "libft.h"
# include "minishell_builtins.h"
# include "minishell_parser.h"

typedef struct s_shell
{
	t_env		*env;
	t_ast		*ast;
	t_token		*tokens;
	int			fd[4];
	int			children;
	int			last_exit_status;
}	t_shell;

// prompt.c

char	*prompt_valid(t_shell *shell, bool minishell);
bool	get_input(t_shell *shell);

// shell.c

void	cleanup(t_shell *shell);
bool	init_shell(t_shell *shell, char **envp);
void	empty_shell(t_shell *shell, bool close_fds);

#endif