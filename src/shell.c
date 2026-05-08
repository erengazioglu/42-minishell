/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:03:20 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/08 15:36:16 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_input(t_shell *shell, char *input)
{
	t_token	*tokens;

	if (!input || !*input)
		return (false);
	tokens = tokenize(input, NULL);
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
	shell->fd[1] = STDOUT_FILENO;
	shell->fd[2] = STDIN_FILENO;
	shell->children = 1;
	return (0);
}

void	cleanup(t_shell *shell)
{
	shell->fd[1] = STDOUT_FILENO;
	shell->fd[2] = STDIN_FILENO;
	shell->children = 1;
	shell->last_exit_status = 0;
}
