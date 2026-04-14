/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:25:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 21:58:12 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"

t_ast	*parse_tokens(t_token *root);

/**
 * @brief Parses a given list of tokens,
 * 		returning a complete AST node.
 * @param root	First element of token list.
 * @param i		Index of splitting character (pipe/and/or).
 * @returns		Fully populated AST node, or `NULL` if error.
 */
t_ast	*parse_node(t_token *root, int i)
{
	t_ast	*ast;
	
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->node.type = NODE_PIPE;
	ast->node.left = parse_leaf(root, i);
	if (!ast->node.left)
		return (free(ast), NULL);
	ast->node.right = parse_tokens(fetch_token(root, i));
	if (!ast->node.right)
		return (free(ast->node.left), free(ast), NULL);
	return (ast);
}

/**
 * @brief Recursively creates an Abstract Syntax Tree (AST)
 * from a given list of tokens.
 * @param root	First element of token list.
 * @returns		Root of AST (`union u_ast`). 
 */
t_ast	*parse_tokens(t_token *root)
{
	int		i;
	t_ast	*ast;

	i = find_token(root, TK_PIPE);
	if (i != -1)
		ast = parse_node(root, i);
	else
		ast = parse_leaf(root, -1);
	return (ast);
}