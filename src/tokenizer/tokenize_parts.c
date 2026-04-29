/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_parts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:07:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/29 15:45:33 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenize_quote(t_token **root, char *line)
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

int	tokenize_dollar(t_token **root, char *line)
{
	int		len;
	t_token	*new;

	line++;
	len = 0;
	while (line[len] && !ft_isspace(line[len]))
		len++;
	new = new_token(TK_DOLLAR, ft_substr(line, 0, len));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len + 1);
}

int	tokenize_pipe(t_token **root, char *line)
{
	int		len;
	t_token	*new;

	line++;
	len = 0;
	while (line[len] && !ft_isspace(line[len]))
		len++;
	new = new_token(TK_PIPE, ft_strdup(""));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len + 1);
}

int	tokenize_word(t_token **root, char *line)
{
	int		len;
	t_token	*new;

	len = 0;
	while (line[len] && !ft_isspace(line[len]))
		len++;
	new = new_token(TK_WORD, ft_substr(line, 0, len));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return (len);
}

int	tokenize_redir(t_token **root, char *line)
{
	t_token	*new;

	new = new_token(TK_REDIR, ft_substr(line, 0, (line[0] == line[1]) + 1));
	if (!new)
		crash("new_token() returned NULL");
	append_token(root, new);
	return ((line[0] == line[1]) + 1);
}
