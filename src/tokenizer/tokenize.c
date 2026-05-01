/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:29:28 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/01 16:28:04 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

void	free_tokens(t_token *root)
{
	t_token	*next;

	while (root)
	{
		next = root->next;
		free(root->content);
		free(root);
		root = next;
	}
}

void	print_token(t_token *token, bool display_count)
{
	int	count;
	if (token == NULL)
		return ;
	ft_printf("Token(type: %d, content: %s)", token->type, token->content);
	count = 0;
	if (display_count)
	{
		while (token->next)
		{
			count++;
			token = token->next;
		}
		ft_printf(" + %d", count);
	}
	ft_putchar('\n', 1, false);
}

void	print_tokens(t_token *root)
{
	ft_printf("%sTokens:\n", YEL);
	while (root)
	{
		print_token(root, false);
		root = root->next;
	}
	ft_printf("%s", RST);
}

t_token	*tokenize(char *line)
{
	t_token	*root;

	root = NULL;
	while (*line && *line != '\n')
	{
		while (ft_isspace(*line))
			line++;
		if (ft_strchr("\"\'", *line, 0, 0))
			line += tokenize_quote(&root, line);
		else if (ft_strchr("<>", *line, 0, 0))
			line += tokenize_redir(&root, line);
		else if (*line == '$')
			line += tokenize_dollar(&root, line);
		else if (*line == '|')
			line += tokenize_pipe(&root);
		else
			line += tokenize_word(&root, line);
	}
	return (root);
}
