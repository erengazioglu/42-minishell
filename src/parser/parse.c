/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:25:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:55:14 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"
#include "minishell.h"

t_ast	*parse_tokens(t_token *root, t_shell *shell);

/**
 * @brief Parses a given list of tokens,
 * 		returning a complete AST node.
 * @param root	First element of token list.
 * @param i		Index of splitting character (pipe/and/or).
 * @returns		Fully populated AST node, or `NULL` if error.
 * @note	If a `NODE_ERR` is generated on the left, the right side
 * is not parsed.
 */
t_ast	*parse_node(t_token *root, int i, t_shell *shell)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->node.type = NODE_PIPE;
	ast->node.left = parse_leaf(&root, i, shell);
	if (!ast->node.left)
		return (free(ast), NULL);
	if (ast->node.left->leaf.type == NODE_ERR)
		return (ast->node.right = NULL, ast);
	ast->node.right = parse_tokens(root->next, shell);
	if (!ast->node.right)
		return (free_tokens(root), free_ast(ast), NULL);
	free(root->content);
	free(root);
	return (ast);
}

/**
 * @brief Recursively creates an Abstract Syntax Tree (AST)
 * from a given list of tokens.
 * @param root	First element of token list.
 * @returns		Root of AST (`union u_ast`), or `NULL` on failure.
 */
t_ast	*parse_tokens(t_token *root, t_shell *shell)
{
	int		i;
	t_ast	*ast;

	i = find_token(root, TK_PIPE);
	if (i == 0)
	{
		ft_putstr("minishell: syntax error near unexpected token '|'",
			STDERR_FILENO, -1, true);
		shell->last_exit_status = 2;
		return (NULL);
	}
	if (i != -1)
		ast = parse_node(root, i, shell);
	else
		ast = parse_leaf(&root, -1, shell);
	if (!ast)
		return (NULL);
	if (ast && ast->leaf.type == NODE_ERR)
	{
		free_tokens(root);
		return (ast);
	}
	return (ast);
}
