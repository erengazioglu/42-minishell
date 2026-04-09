/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_parts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:07:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/09 19:19:59 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		tokenize_quote(t_token *root, char *line)
{
	int		len;
	char	quote;
	t_token	*new;

	quote = *line;
	line++;
	len = 0;
	while (line[len] && line[len] != quote)
		len++;
	if (line[len] != quote)
		crash("unmatched quote");
	if (quote == '"')
		new = new_token(TK_DQUOTE, ft_substr(line, 0, len));
	else
		new = new_token(TK_SQUOTE, ft_substr(line, 0, len));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len + 2);
}
int		tokenize_dollar(t_token *root, char *line)
{
	int		len;
	t_token	*new;

	line++;
	len = 0;
	while (line[len] && !ft_isspace(*line))
		len++;
	new = new_token(TK_DOLLAR, ft_substr(line, 0, len));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len + 1);	
}

int		tokenize_word(t_token *root, char *line)
{
	int		len;
	t_token	*new;

	len = 0;
	while (line[len] && !ft_isspace(*line))
		len++;
	new = new_token(TK_DOLLAR, ft_substr(line, 0, len));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len);	
}
