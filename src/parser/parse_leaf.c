/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_leaf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:21:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/14 00:54:28 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"

// int	count_redirs(t_token *root, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (root && n--)
// 	{
// 		if (root->type == TK_REDIR)
// 		{
// 			if (!root->next
// 				|| root->next->type != TK_PIPE
// 				|| root->next->type != TK_REDIR)
// 				return (-1);
// 			i++;
// 		}
// 		root = root->next;
// 	}
// 	return (i);
// }

// bool	*parse_args(t_ast *ast, t_token *root, int n)
// {
	
// }
// void	get_redirect()


// /**
//  * @brief Parses the redirections of a list of tokens, and fills in
//  * for the AST leaf (or leaves it NULL if no redirections).
//  * @param ast	AST leaf to be populated.
//  * @param token	First element of token list.
//  * @param n		Number of tokens to parse. If `n < 0` or bigger than the number
//  * of elements in the list, parses all tokens forward from `root`.
//  * @returns		`true` on success, `false` if errors.
//  */
// bool	*parse_redirs(t_ast *ast, t_token *root, int n)
// {
// 	int	i;

// 	i = count_redirs(root, n);
// 	if (i == -1)
// 	{
// 		ast->err.type = NODE_ERR;
// 		ast->err.err = ERR_PARSE_REDIR;
// 		return (false);
// 	}
// 	if (!i)
// 		return (true);
// 	ast->leaf.redirs = ft_calloc(i + 1, sizeof(t_redir));
// 	if (!ast->leaf.redirs)
// 		return (false);
// 	i = 0;
// 	while (root && n--)
// 	{
// 		if (root->type == TK_REDIR)
// 		{
// 			(ast->leaf.redirs + i)->target = root->next;
// 			(ast->leaf.redirs + i++)->type = root->content;
// 			root = root->next;
// 		}
// 		root = root->next;
// 	}
// 	return (true);
// }

t_redir	*redir_get(t_redir *redir, int i)
{
	if (i < 0)
	{
		while (redir->next)
			redir = redir->next;
		return (redir);
	}
	while (redir->next && i--)
	{
		redir = redir->next;
	}
}

t_redir	*new_redir(t_redirtype type, t_token *target)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	redir->type = type;
	redir->target = target;
	return (redir);
}

t_token	*parse_token(t_ast *ast, t_token *tkn, int *n)
{
	if (tkn->type == TK_REDIR)
	{
		if (!tkn->next)
			return (NULL); // crash here!
		if (!ast->leaf.redirs)
			ast->leaf.redirs = new_redir(tkn->content, tkn->next);
		else
		ast->leaf.redirs 
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
t_ast	*parse_leaf(t_token *root, int n)
{
	t_ast	*ast;
	t_redir	*redir;
	int		redir_count;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	while (root)
	{
		root = parse_token(ast, root, &n);
		if (ast->err.type == NODE_ERR)
			return (NULL) // cleanup here...
	}


}