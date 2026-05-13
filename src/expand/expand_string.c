/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:29:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:36:10 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_string_var(char *result, char **str, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	var_name = pick_var_name(str);
	if (!var_name)
		return (ft_strjoin(result, "$", -1, true));
	var_value = ft_getenv(shell, var_name);
	free(var_name);
	if (var_value)
	{
		result = ft_strjoin(result, var_value, -1, true);
		free(var_value);
	}
	return (result);
}

char	*expand_string_word(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	quote;

	temp = str;
	result = ft_strdup("");
	quote = 0;
	while (*temp)
	{
		if (!quote && (*temp == '\'' || *temp == '\"'))
			quote = *temp++;
		else if (quote && *temp == quote)
		{
			quote = 0;
			temp++;
		}
		else if ((!quote || quote == '\"') && *temp == '$')
			result = expand_string_var(result, &temp, shell);
		else
			result = ft_strjoin(result, temp++, 1, true);
	}
	free(str);
	return (result);
}

char	*expand_string_dquote(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	buf[2];

	temp = str;
	result = ft_strdup("");
	buf[1] = '\0';
	while (*temp)
	{
		if (*temp == '$')
			result = expand_string_var(result, &temp, shell);
		else
		{
			buf[0] = *temp++;
			result = ft_strjoin(result, buf, -1, true);
		}
	}
	free(str);
	return (result);
}
