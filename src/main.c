/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/07 12:55:13 by jalfaiat         ###   ########.fr       */
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
	char	*line;
	t_token	*tokens;
	t_ast	*ast;
	char	*temp;
	t_shell	shell;

	(void) argc;
	(void) argv;
	shell.env = env_from_envp(envp);
	shell.last_exit_status = 0;
	while (1)
	{
		set_interactive_signals();
		line = readline("minishell> ");
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr("exit\n", 2, -1, true);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if (*temp)
		{
			tokens = tokenize(line);
			// print_tokens(tokens);
			ast = parse_tokens(tokens);
			if (ast)
			{
				// print_ast(ast);
				shell.last_exit_status = dispatch(ast, &shell);
				free_ast(ast);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
