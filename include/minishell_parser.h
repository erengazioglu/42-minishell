/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:00:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 13:17:40 by egaziogl         ###   ########.fr       */
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
	NODE_CMD
}	t_asttype;

typedef struct s_redir
{
	t_redirtype	type;
	char		*target;
}	t_redir;

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
	char		**argv;
	t_redir		*redirs;
}	t_astleaf;

typedef union u_ast
{
	t_astnode	node;
	t_astleaf	leaf;
}	t_ast;

t_ast	*parse_tokens(t_token *root);

#endif