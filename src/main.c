/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/07 18:15:30 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/**
 * @brief Entry point for minishell.
 *
 * Initializes the shell environment from @p envp, then enters a readline()
 * loop. For each non-empty input line it tokenizes, parses into an AST, and
 * dispatches execution, tracking the last exit status.
 *
 * @param argc Unused.
 * @param argv Unused.
 * @param envp Environment array used to build the internal env list.
 * @return Always 0 (normal termination via EOF).
 */
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
	t_shell	shell;

	(void) argc;
	(void) argv;
	init_shell(&shell, envp);
	while (1)
	{
		set_interactive_signals();
		input = get_input();
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr("exit\n", 2, -1, true);
			break ;
		}
		if (*input)
		{
			tokens = tokenize(input);
			ast = parse_tokens(tokens);
			if (ast)
			{
				shell.last_exit_status = dispatch(ast, &shell);
				free_ast(ast);
			}
		}
		free(input);
	}
	free_env(shell.env);
	rl_clear_history();
	return (0);
}
