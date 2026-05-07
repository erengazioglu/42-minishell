/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:03:20 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 19:17:43 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_input(t_shell *shell, char *input)
{
	t_token	*tokens;

	if (!*input)
		return (false);
	tokens = tokenize(input);
	free(input);
	if (!tokens)
		return (false);
	shell->ast = parse_tokens(tokens);
	if (!shell->ast)
	{
		free_tokens(tokens);
		return (false);
	}
	return (true);
}

// TODO: return exit code or something useful
int	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_from_envp(envp);
	shell->last_exit_status = 0;
	shell->hdoc = NULL;
	return (0);
}