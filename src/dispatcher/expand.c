/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:12:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 17:09:43 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(char *result, char **str, t_shell *shell)
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

static char	*expand_string_word(char *str, t_shell *shell)
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
			result = expand_var(result, &temp, shell);
		else
			result = ft_strjoin(result, temp++, 1, true);
	}
	free(str);
	return (result);
}

static char	*expand_string_dquote(char *str, t_shell *shell)
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
			result = expand_var(result, &temp, shell);
		else
		{
			buf[0] = *temp++;
			result = ft_strjoin(result, buf, -1, true);
		}
	}
	free(str);
	return (result);
}

/**
 * @brief Expand variables inside redirection targets.
 *
 * Updates each redirection's target token content in-place.
 *
 * @param root First redirection node.
 * @param shell Shell context used for environment lookup.
 */
void	expand_redirs(t_redir *root, t_shell *shell)
{
	t_token	*tkn;

	while (root)
	{
		tkn = root->target;
		if (tkn->type == TK_WORD)
			tkn->content = expand_string_word(tkn->content, shell);
		else if (tkn->type == TK_DQUOTE)
			tkn->content = expand_string_dquote(tkn->content, shell);
		root = root->next;
	}
}

/**
 * @brief Expand variables inside command tokens.
 *
 * Updates token content in-place for word and double-quoted tokens.
 *
 * @param root First token node.
 * @param shell Shell context used for environment lookup.
 */
bool	expand_tokens(t_token *root, t_shell *shell)
{
	if (!root)
		return (false);
	while (root)
	{
		if (root->type == TK_WORD)
			root->content = expand_string_word(root->content, shell);
		else if (root->type == TK_DQUOTE)
			root->content = expand_string_dquote(root->content, shell);
		root = root->next;
	}
	return (true);
}
