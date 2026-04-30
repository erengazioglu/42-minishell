/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:10:44 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/29 15:45:52 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

/**
 * @brief Returns the index of a given token type, or -1 if it fails.
 * @param root	List element to start counting from.
 * @param type	Token type to search for.
 * @return		Index of the first occurrence of the token type, or -1 if not found.
 */
int	find_token(t_token *root, t_ttype type)
{
	int	i;

	i = 0;
	while (root)
	{
		if (root->type == type)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

/**
 * @brief	Creates a new token.
 * @param type		Token type (as defined by the ttype enum).
 * @param content	Content of the token (must be malloced for it to work).
 * @return	The new token node.
 */
t_token	*new_token(t_ttype type, char *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = content;
	token->next = NULL;
	return (token);
}

/**
 * @brief	Appends a token to the end of a token list.
 * @param root	Pointer to the first element of the token list. 
 * If `*root` is `NULL`, the new token becomes the first element.
 * @param new	Token to append.
 * @return	None. Modifies the list in place.
 */
void	append_token(t_token **root, t_token *new)
{
	t_token	*temp;

	if (!(*root))
	{
		*root = new;
		return ;
	}
	temp = *root;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
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

/**
 * @brief	Creates a copy of the given token.
 * @param tkn	Token to clone.
 * @param deep	If `true`, also duplicates the content string.
 * @return	Cloned token.
 */
t_token	*clone_token(t_token *tkn, bool deep)
{
	if (deep)
		return (new_token(tkn->type, ft_strdup(tkn->content)));
	else
		return (new_token(tkn->type, tkn->content));
}