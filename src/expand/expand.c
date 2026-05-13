/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:12:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 01:41:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*harvest_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	var_name = pick_var_name(&str);
	*i += 1;
	if (!var_name)
		return (ft_strdup("$"));
	var_value = ft_getenv(shell, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	*i += ft_strlen(var_name);
	free(var_name);
	return (var_value);
}

static char	*expand_vars_init(int *start, int *end)
{
	*start = 0;
	*end = 0;
	return (ft_strdup(""));
}

void	expand_vars(t_token *tkn, t_shell *shell)
{
	char	*new;
	char	*temp;
	int		start;
	int		end;

	if (tkn->type != TK_WORD && tkn->type != TK_DQUOTE)
		return ;
	new = expand_vars_init(&start, &end);
	while (tkn->content[end])
	{
		while (tkn->content[end] && tkn->content[end] != '$')
			end++;
		temp = ft_substr(tkn->content, start, end - start);
		new = ft_strjoin(new, temp, -1, true);
		free(temp);
		if (tkn->content[end] == '$')
		{
			temp = harvest_var(tkn->content + end, &end, shell);
			new = ft_strjoin(new, temp, -1, true);
			free(temp);
			start = end;
		}
	}
	free(tkn->content);
	tkn->content = new;
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
bool	expand_tokens(t_token **root, t_shell *shell)
{
	t_token	*temp;

	if (!*root)
		return (false);
	temp = *root;
	while (temp)
	{
		expand_vars(temp, shell);
		temp = temp->next;
	}
	*root = explode_tokens(*root);
	temp = *root;
	while (temp)
	{
		if (temp->type == TK_WORD)
			temp->content = expand_string_word(temp->content, shell);
		else if (temp->type == TK_DQUOTE)
			temp->content = expand_string_dquote(temp->content, shell);
		temp = temp->next;
	}
	return (true);
}
