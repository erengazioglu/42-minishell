/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:03:20 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:13:45 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Function to have shell prompt for user input, and tokenize.
 * @return	`true` on success, `false` on failure (e.g. double pipe).
 */
bool	get_input(t_shell *shell)
{
	char	*input;

	set_interactive_signals();
	input = prompt_valid(shell, true);
	shell->tokens = tokenize(input, NULL);
	free(input);
	while (fetch_token(shell->tokens, -1)->type == TK_PIPE)
	{
		if (!fetch_token(shell->tokens, -2)
				|| fetch_token(shell->tokens, -2)->type == TK_PIPE)
			return (free_tokens(shell->tokens), shell->tokens = NULL, false);
		input = prompt_valid(shell, false);
		shell->tokens = tokenize(input, shell->tokens);
		free(input);
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
	shell->tokens = NULL;
}

void	empty_shell(t_shell *shell)
{
	free_env(shell->env);
	if (shell->tokens)
		free_tokens(shell->tokens);
	rl_clear_history();
}
