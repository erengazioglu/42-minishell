/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:45:56 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:47:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns the index of a given token type, or -1 if it fails.
 * @param root	List element to start counting from.
 * @param type	Token type to search for.
 * @return		Index of the first occurrence of the token type, or
			-1 if not found.
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

static int	count_tokens(t_token *start)
{
	int	i;

	i = 0;
	while (start)
	{
		start = start->next;
		i++;
	}
	return (i);
}

/**
 * @brief Returns the token at index i, or NULL if it fails.
 * @param start	List element to start counting from.
 * @param i		Index to fetch. If bigger than total size, will return NULL.
 * If negative, counts from the end of the list (-1 returns the last element).
 * @return		Token `i` elements away from `start`.
 */
t_token	*fetch_token(t_token *start, int i)
{
	if (!start)
		return (NULL);
	if (i < 0)
		i += count_tokens(start);
	if (i < 0)
		return (NULL);
	while (start && i--)
		start = start->next;
	return (start);
}
