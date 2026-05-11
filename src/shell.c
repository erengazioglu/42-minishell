/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:03:20 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/11 21:49:14 by egaziogl         ###   ########.fr       */
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

/**
 * @brief	Initializes shell.
 * @param shell
 * @return	True if successful, false if failed.
 * @note	Does not malloc an actual shell struct.
 */
bool	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_from_envp(envp);
	if (!shell->env)
		return (false);
	shell->last_exit_status = 0;
	shell->fd[0] = -1;
	shell->fd[1] = STDOUT_FILENO;
	shell->fd[2] = STDIN_FILENO;
	shell->fd[3] = -1;
	shell->children = 1;
	shell->tokens = NULL;
	return (true);
}

void	cleanup(t_shell *shell)
{
	shell->fd[0] = -1;
	shell->fd[1] = STDOUT_FILENO;
	shell->fd[2] = STDIN_FILENO;
	shell->fd[3] = -1;
	shell->children = 1;
	// shell->last_exit_status = 0;
	shell->tokens = NULL;
}

void	empty_shell(t_shell *shell)
{
	free_env(shell->env);
	if (shell->tokens)
		free_tokens(shell->tokens);
	rl_clear_history();
}
