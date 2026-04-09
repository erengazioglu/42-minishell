/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:29:28 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/09 18:32:23 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

void	print_tokens(t_token *root)
{
	while (root)
	{
		ft_printf("Token(type=%d,content=%s)\n", root->type, root->content);
		root = root->next;
	}
}

void	tokenize(char *line)
{
	t_token	*root;

	root = NULL;
	while (*line != '\n')
	{
		while (ft_isspace(*line))
			line++;
		if (ft_strchr("\"\'", *line, 0, 0))
			line += tokenize_quote(root, line);
		else if (*line == '$')
			line += tokenize_dollar(root, line);
		else
			line += tokenize_word(root, line);
	}
	return (root);
}
