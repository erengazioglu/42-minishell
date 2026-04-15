/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:31:14 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/15 17:20:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKENIZER_H
# define MINISHELL_TOKENIZER_H

# include "../libft/include/libft.h"

typedef enum	e_ttype
{
	TK_NONETYPE,
	TK_REDIR,
	TK_WORD,
	TK_DQUOTE,
	TK_SQUOTE,
	TK_OPT,
	TK_PIPE,
	TK_DOLLAR
}	t_ttype;

typedef struct	s_token
{
	t_ttype			type;
	char			*content;
	struct s_token	*next;
}	t_token;

// tokenizer/util.c

t_token	*new_token(t_ttype type, char *content);
t_token	*fetch_token(t_token *start, int i);
void	append_token(t_token **root, t_token *new);
int		find_token(t_token *root, t_ttype type);

// tokenizer/tokenize.c

t_token	*tokenize(char *line);
void	free_tokens(t_token *root);
void	print_tokens(t_token *root);

// tokenizer/tokenize_parts.c

int		tokenize_quote(t_token **root, char *line);
int		tokenize_dollar(t_token **root, char *line);
int		tokenize_word(t_token **root, char *line);
int		tokenize_redir(t_token **root, char *line);
int		tokenize_pipe(t_token **root, char *line);


#endif
