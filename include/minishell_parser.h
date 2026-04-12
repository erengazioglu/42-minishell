/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 23:00:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 00:24:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKENIZER_H
# define MINISHELL_TOKENIZER_H

# include "../libft/include/libft.h"

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

typedef struct s_ast t_ast;
typedef struct s_astnode
{
	t_ast	*left;
	t_ast	*right;
}	t_astnode;

typedef struct s_astleaf
{
	int		argc;
	char	**argv;
	t_redir	*redirs;
}	t_astleaf;

struct s_ast
{
	t_asttype	type;
	union {
		t_astnode	node;
		t_astleaf	leaf;
	};
};

#endif