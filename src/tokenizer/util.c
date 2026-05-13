/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:10:44 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:47:08 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

int	get_word_len(char *line)
{
	int	len;
	int	in_sq;
	int	in_dq;

	len = 0;
	in_sq = 0;
	in_dq = 0;
	while (line[len])
	{
		if (line[len] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (line[len] == '"' && !in_sq)
			in_dq = !in_dq;
		if (!in_sq && !in_dq && (ft_isspace(line[len])
				|| ft_strchr("<>|", line[len], 0, 0)))
			break ;
		len++;
	}
	return (len);
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
