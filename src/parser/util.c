/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:01:06 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:27:36 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"

/**
 * @brief Appends a redirection to the end of a redirection list.
 * @param root	Pointer to the first element of the redirection list.
 * If `*root` is `NULL`, the new redir becomes the first element.
 * @param new	Redirection to append.
 */
void	append_redir(t_redir **root, t_redir *new)
{
	t_redir	*temp;

	if (!new)
		return ;
	if (!*root)
	{
		*root = new;
		return ;
	}
	temp = *root;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	free_astleaf(t_ast *ast)
{
	t_token	*arg;
	t_token	*a_temp;
	t_redir	*redir;
	t_redir	*r_temp;

	arg = ast->leaf.argv;
	while (arg)
	{
		a_temp = arg;
		arg = arg->next;
		free(a_temp->content);
		free(a_temp);
	}
	redir = ast->leaf.redirs;
	while (redir)
	{
		r_temp = redir;
		redir = redir->next;
		if (r_temp->fd != -1)
			close(r_temp->fd);
		free(r_temp->target->content);
		free(r_temp->target);
		free(r_temp);
	}
}

/**
 * @brief Given a root node, frees the whole AST tree recursively.
 * @param ast	Root of the AST to free.
 */
void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->node.type == NODE_PIPE)
	{
		free_ast(ast->node.left);
		free_ast(ast->node.right);
	}
	else if (ast->node.type == NODE_CMD)
		free_astleaf(ast);
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
		if (*(type + 1) == '<')
			redir->type = REDIR_HEREDOC;
		else
			redir->type = REDIR_IN;
	}
	else if (*type == '>')
	{
		if (*(type + 1) == '>')
			redir->type = REDIR_APPEND;
		else
			redir->type = REDIR_TRUNC;
	}
	redir->target = target;
	redir->fd = -1;
	return (redir);
}
