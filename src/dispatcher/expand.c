/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:12:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 17:39:27 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pick_var_name(char **str)
{
	int		i;
	char	*result;

	(*str)++;
	if (!(**str) || ft_isspace(**str))
		return (NULL);
	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]))
		i++;
	result = ft_substr(*str, 0, i);
	*str += i;
	return (result);
}

static char	*advance(char *result, char **str)
{
	int	len;

	len = 0;
	while ((*str)[len] && (*str)[len] != '$')
		len++;
	result = ft_strjoin(result, ft_substr(*str, 0, len), -1, true);
	*str += len;
	return (result);
}

static char	*expand_var(char *result, char **str)
{
	char	*var_name;
	char	*var_value;

	var_name = pick_var_name(str);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	free(var_name);
	if (var_value)
		result = ft_strjoin(result, var_value, -1, true);
	return (result);
}

/**
 * @brief	Expands the variables in a token (in place).
 * @param tkn	Token to be expanded.
 */
static char	*expand_string(char *str)
{
	char	*result;
	char	*temp;

	temp = str;
	result = ft_strdup("");
	while (*temp)
	{
		if (*temp == '$')
			result = expand_var(result, &temp);
		else
			result = advance(result, &temp);
	}
	free(str);
	return(result);
}

void	expand_tokens(t_token *root)
{
	while (root)
	{
		if (root->type == TK_WORD || root->type == TK_DQUOTE)
			root->content = expand_string(root->content);
		root = root->next;
	}
}
