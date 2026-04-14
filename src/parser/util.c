/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:01:06 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 21:57:42 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"
#include "../../include/minishell_parser.h"

int	find_node(t_token *root)
{
	int	i;

	i = 0;
	while (root)
	{
		if (root->type == TK_PIPE)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

void	free_ast(t_ast *ast)
{
	if (ast->node.type == NODE_PIPE)
	{
		free_ast(ast->node.left);
		free_ast(ast->node.right);
	}
	else
		free(ast);
}

/**
 * @brief Returns the token at index i, or NULL if it fails.
 * @param start	List element to start counting from.
 * @param i		Index to fetch. If bigger than total size, will return NULL.
 * @return		Token `i` elements away from `start`.
 */
t_token	*fetch_token(t_token *start, int i)
{
	while (start && i--)
		start = start->next;
	return (start);
}
