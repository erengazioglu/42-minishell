/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:00:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 23:50:24 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "../libft/include/libft.h"
# include "minishell_tokenizer.h"

typedef enum e_redirtype
{
	REDIR_IN,
	REDIR_APPEND,
	REDIR_TRUNC,
	REDIR_HEREDOC
}	t_redirtype;

typedef enum e_asttype
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD,
	NODE_ERR
}	t_asttype;

typedef enum e_err_parse
{
	ERR_PARSE_REDIR,	// syntax error near unexpected token ">"
	ERR_PARSE_PIPE		// syntax error near pipe "|"
}	t_err_parse;

typedef struct s_redir t_redir;
struct s_redir
{
	t_redirtype	type;
	t_token		*target;
	t_redir		*next;
};

typedef union u_ast t_ast;
typedef struct s_astnode
{
	t_asttype	type;
	t_ast	*left;
	t_ast	*right;
}	t_astnode;

typedef struct s_astleaf
{
	t_asttype	type;
	int			argc;
	t_token		*argv;
	t_redir		*redirs;
}	t_astleaf;

typedef struct s_asterr
{
	t_asttype	type;
	t_err_parse	err;
}	t_asterr;


typedef union u_ast
{
	t_astnode	node;
	t_astleaf	leaf;
	t_asterr	err;
}	t_ast;

// parser/parse.c

t_ast	*parse_tokens(t_token *root);

// parser/util.c

t_token	*fetch_token(t_token *start, int i);

#endif