/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:49:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:31:19 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand.c

void	expand_redirs(t_redir *root, t_shell *shell);
bool	expand_tokens(t_token **root, t_shell *shell);

// util.c

char    *ft_strslice(char **str, int start, int len);
t_token *explode_tokens(t_token *root);

// expand_string.c

char	*expand_string_word(char *str, t_shell *shell);
char	*expand_string_dquote(char *str, t_shell *shell);
