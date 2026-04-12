/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:10:44 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/12 20:27:06 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

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
