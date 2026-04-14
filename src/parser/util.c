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

/**
 * @brief Appends a redirection to the end of a redirection list.
 * @param root	First element of redirection list.
 * @param new	Redirection to append.
 */
void	append_redir(t_redir *root, t_redir *new)
{
	if (!root && !new)
		return ;
	while (root->next)
		root = root->next;
	root->next = new;
}

/**
 * @brief Given a root node, frees the whole AST tree recursively.
 * @param ast	Root of the AST to free.
 */
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
 * @brief	Given a root node, returns the redirection 
 * at index `i` in the list.
 * @param redir	First element of redirection list.
 * @param i		Index of redirection to fetch. 
 * If `i` >= number of redirections or < 0, 
 * returns the last redirection in the list.
 * @returns		Redirection at index `i`. 
 */
t_redir	*fetch_redir(t_redir *redir, int i)
{
	while (redir->next && i--)
		redir = redir->next;
	return (redir);
}

/**
 * @brief	Creates a new redirection with the given type and target token.
 * @param type		Type of redirection ("<", ">", ">>", "<<").
 * @param target	Token representing the target of the redirection 
 * (e.g. quoted file name, variable...).
 * @returns		Pointer to the newly created redirection, 
 * or `NULL` on allocation failure.
 * @note	Assumes the `type` string is formatted correctly.
 */
t_redir	*new_redir(char *type, t_token *target)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	if (*type == '<')
	{
		if (*(type + 1))
			redir->type = REDIR_HEREDOC;
		else
			redir->type = REDIR_IN;
	}
	else if (*type == '>')
	{
		if (*(type + 1))
			redir->type = REDIR_APPEND;
		else
			redir->type = REDIR_TRUNC;
	}
	redir->target = target;
	return (redir);
}
