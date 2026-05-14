/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_leaf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:21:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 16:34:32 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*print_unexpected_error(t_token *err, char *tkn, t_shell *sh)
{
	ft_putstr("minishell: syntax error near unexpected token '",
		STDERR_FILENO, -1, false);
	ft_putstr(tkn, STDERR_FILENO, -1, false);
	ft_putchar('\'', STDERR_FILENO, true);
	sh->last_exit_status = 2;
	return (err);
}

/**
 * @brief Checks if the current token will raise an unexpected token error,
 * 	and creates an "error node" accordingly.
 * @param tkn	The token to be checked.
 * @returns		Error token, or NULL if everything is in order.
 * @note	The error token is completely empty, with a `TK_ERR` type,
 * 	but still a valid token that can be used to add contextual info.
 */
t_token	*check_unexpected_token(t_token *tkn, t_shell *shell)
{
	t_token	*err;

	err = ft_calloc(1, sizeof(t_token));
	err->type = TK_ERR;
	if (tkn->type == TK_REDIR)
	{
		if (!tkn->next)
		{
			shell->last_exit_status = 2;
			return (print_unexpected_error(err, "newline", shell));
		}
		if (tkn->next->type == TK_PIPE || tkn->next->type == TK_REDIR)
			return (print_unexpected_error(err, tkn->next->content, shell));
	}
	else if (tkn->type == TK_PIPE && !tkn->next)
		return (print_unexpected_error(err, "|", shell));
	return (free(err), NULL);
}

/**
 * @brief Parses one token, fills in the AST leaf accordingly,
 * and returns the next token to parse.
 * @param ast	AST leaf to be populated.
 * @param tkn	Current token to parse.
 * @param n		A pointer to the number of tokens left to parse.
 * Decremented by this function for each token parsed.
 * @returns		Next token to parse (or `NULL` if finished/error).
 * @note	On error, fills in the AST leaf with error information.
 * @note	Error handling may leak memory!
 */
t_token	*parse_leaf_step(t_ast *ast, t_token *tkn, int *n, t_shell *shell)
{
	t_token	*retval;

	retval = check_unexpected_token(tkn, shell);
	if (retval)
		return (free_tokens(tkn), retval);
	if (tkn->type == TK_REDIR)
	{
		append_redir(&ast->leaf.redirs, new_redir(tkn->content,
				clone_token(tkn->next, false)));
		retval = tkn->next->next;
		*n -= 2;
		return (free(tkn->next), free(tkn->content), free(tkn), retval);
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
 * @param root	Pointer to first element of token list.
 * @param n		Number of tokens to parse. If `n < 0` or bigger than the number
 * of elements in the list, parses all tokens forward from `root`.
 * @note	Advances the `root` parameter.
 * @returns		Fully populated AST leaf, or `NULL` if error.
 */
t_ast	*parse_leaf(t_token **root, int n, t_shell *shell)
{
	t_ast	*ast;
	t_token	*temp;

	temp = *root;
	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->leaf.type = NODE_CMD;
	while (temp && n)
	{
		temp = parse_leaf_step(ast, temp, &n, shell);
		if (temp && temp->type == TK_ERR)
		{
			free_tokens(temp);
			free_ast(ast, true);
			return (NULL);
		}
	}
	*root = temp;
	return (ast);
}
