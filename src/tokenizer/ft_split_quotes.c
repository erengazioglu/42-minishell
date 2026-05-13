/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:37:38 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:44:04 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tokenizer.h"

// quote[0] = single quote
// quote[1] = double quote
static int	count_tokens(const char *str)
{
	bool	quote[2];
	int		count;

	quote[0] = false;
	quote[1] = false;
	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		count++;
		while (*str && (!ft_isspace(*str) || quote[0] || quote[1]))
		{
			if (*str == '\'' && !quote[1])
				quote[0] = !quote[0];
			else if (*str == '"' && !quote[0])
				quote[1] = !quote[1];
			str++;
		}
	}
	if (quote[0] || quote[1])
		return (-1);
	return (count);
}

static int	get_token_len(const char *str)
{
	int	in_sq;
	int	in_dq;
	int	len;

	in_sq = 0;
	in_dq = 0;
	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[len] == '"' && !in_sq)
			in_dq = !in_dq;
		if (ft_isspace(str[len]) && !in_sq && !in_dq)
			break ;
		len++;
	}
	return (len);
}

static char	*dup_token(const char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

static char	**init_split(const char *str, int *tokens)
{
	char	**out;

	if (!str)
		return (NULL);
	*tokens = count_tokens(str);
	if (*tokens < 0)
		return (NULL);
	out = ft_calloc(*tokens + 1, sizeof(char *));
	if (!out)
		return (NULL);
	return (out);
}

char	**ft_split_quotes(const char *str)
{
	char	**out;
	int		tokens;
	int		i;
	int		len;

	out = init_split(str, &tokens);
	if (!out)
		return (NULL);
	i = -1;
	while (++i < tokens)
	{
		while (*str && ft_isspace(*str))
			str++;
		len = get_token_len(str);
		out[i] = dup_token(str, len);
		if (!out[i])
			return (free_strarr(out), NULL);
		str += len;
	}
	return (out);
}
