/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:00:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 23:43:10 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include "../libft/include/libft.h"
# include "minishell_tokenizer.h"

typedef enum e_redirtype
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_APPEND,
	REDIR_TRUNC
}	t_redirtype;

typedef enum e_asttype
{
	NODE_NONE,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD,
	NODE_ERR
}	t_asttype;

typedef enum e_err_parse
{
	ERR_PARSE_NONE,
	ERR_PARSE_UNCLOSED_QUOTE,	// syntax error: unclosed quote
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
	t_ast		*left;
	t_ast		*right;
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

// parser/parse_leaf.c

t_ast	*parse_leaf(t_token **root, int n);

// parser/util.c

void	append_redir(t_redir **root, t_redir *new);
void	free_ast(t_ast *ast);
t_redir	*fetch_redir(t_redir *redir, int i);
t_redir	*new_redir(char *type, t_token *target);

#endif