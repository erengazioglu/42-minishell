/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_leaf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:21:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/30 15:47:29 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"

/**
 * @brief Parses one token, fills in the AST leaf accordingly,
 * and returns the next token to parse.
 * @param ast	AST leaf to be populated.
 * @param tkn	Current token to parse.
 * @param n		A pointer to the number of tokens left to parse. 
 * Decremented by this function for each token parsed.
 * @returns		Next token to parse (or `NULL` if finished/error).
 * @note	On error, fills in the AST leaf with error information.
 */
t_token	*parse_leaf_step(t_ast *ast, t_token *tkn, int *n)
{
	t_token	*retval;

	if (tkn->type == TK_REDIR)
	{
		if (!tkn->next || tkn->next->type == TK_PIPE
			|| tkn->next->type == TK_OPT)
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", 
				tkn->next->content);
			return (NULL); // crash and error here!
		}
		append_redir(&ast->leaf.redirs, 
			new_redir(tkn->content, clone_token(tkn->next, false)));
		retval = tkn->next->next;
		*n -= 2;
		return (free(tkn->next), free(tkn), retval);
	}
	else
	{
		append_token(&ast->leaf.argv, clone_token(tkn, false));
		*n -= 1;
		retval = tkn->next;
		ast->leaf.argc++;
		return (free(tkn), retval);
	}
}

/**
 * @brief Parses a given list of tokens (up to n tokens),
 * 		returning a complete AST leaf.
 * @param root	First element of token list.
 * @param n		Number of tokens to parse. If `n < 0` or bigger than the number
 * of elements in the list, parses all tokens forward from `root`.
 * @returns		Fully populated AST leaf, or `NULL` if error.
 */
t_ast	*parse_leaf(t_token **root, int n)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->leaf.type = NODE_CMD;
	while (*root && n)
	{
		*root = parse_leaf_step(ast, *root, &n);
		if (ast->node.type == NODE_ERR)
			return (NULL); // cleanup here...
	}
	return (ast);
}
