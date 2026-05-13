/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:22:38 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 03:27:52 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	while (str[*i] && str[*i] != quote)
		*i += 1;
	if (str[*i])
		*i += 1;
}

static void skip_letters(char *str, int *i)
{
	while (
		str[*i]
		&& !ft_isspace(str[*i])
		&& str[*i] != '\"'
		&& str[*i] != '\'')
		*i += 1;
}

static t_token	*slice_token(t_token *token, int *i)
{
	t_token	*new;
	char	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = TK_WORD;
	new->content = ft_strslice(&token->content, 0, *i);
	new->next = token;
	*i = 0;
	while (ft_isspace(token->content[*i]))
		*i += 1;
	temp = token->content;
	token->content = ft_strdup(temp + *i);
	free(temp);
	*i = 0;
	return (new);
}

static t_token	*token_wordsplit(t_token *token)
{
	t_token	*new;
	char	*str;
	char	quote;
	int		i;

	str = token->content;
	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (ft_isspace(str[i]))
		{
			append_token(&new, slice_token(token, &i)); // creates new token; skips whitespace; advances i;
			str = token->content;
		}
		else
			i++;
	}
	if (!new)
		return (token);
	return (new);
}

/**
 * @brief Split word tokens into multiple tokens based on whitespace after expansion.
 * @note	Used for variable expansion (e.g. export b="ls -la").
 */
t_token	*explode_tokens(t_token *root)
{
	t_token *new_root;
	t_token *cur;

	if (!root)
		return (NULL);
	new_root = NULL;
	cur = root;
	while (cur)
	{
		if (cur->type == TK_WORD)
		{
			cur = root->next;
			root->next = NULL;
			append_token(&new_root, token_wordsplit(root));
			root = cur;
		}
		else
		{
			cur = root->next;
			root->next = NULL;
			append_token(&new_root, cur);
			root = cur;
		}
	}
	return (new_root);
}
