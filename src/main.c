/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/12 01:56:58 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Entry point for minishell. Gets input, parses it into an AST,
 * and calls `dispatch` when all conditions are met.
 * @param argc Unused.
 * @param argv Unused.
 * @param envp Environment array used to build the internal env list.
 * @return Always 0 (normal termination via EOF).
 * @note	`shell.tokens` is set to NULL to avoid calling free_tokens
 * on a stale reference.
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	if (!init_shell(&shell, envp))
		crash_main("minishell: malloc error", NULL);
	while (true)
	{
		if (!get_input(&shell))
		{
			ft_putstr("minishell: syntax error near unexpected token '|'",
				STDERR_FILENO, -1, true);
				shell.last_exit_status = 2;
			continue;
		}
		shell.ast = parse_tokens(shell.tokens, &shell);
		if (shell.ast)
		{
			shell.tokens = NULL;
			shell.last_exit_status = dispatch(&shell);
			free_ast(shell.ast);
		}
		cleanup(&shell);
	}
	empty_shell(&shell);
	return (0);
}
