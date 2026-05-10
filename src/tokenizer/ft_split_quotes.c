/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolopes <joaolopes@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 00:00:00 by joaolopes         #+#    #+#             */
/*   Updated: 2026/05/09 00:00:00 by joaolopes        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_tokenizer.h"

static int	count_tokens(const char *str)
{
	int	in_sq;
	int	in_dq;
	int	count;

	in_sq = 0, in_dq = 0, count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		count++;
		while (*str && (!ft_isspace(*str) || in_sq || in_dq))
		{
			if (*str == '\'' && !in_dq)
				in_sq = !in_sq;
			else if (*str == '"' && !in_sq)
				in_dq = !in_dq;
			str++;
		}
	}
	return ((in_sq || in_dq) ? -1 : count);
}

static int	get_token_len(const char *str)
{
	int	in_sq;
	int	in_dq;
	int	len;

	in_sq = 0, in_dq = 0, len = 0;
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
	int	tokens;
	int	i;
	int	len;

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
