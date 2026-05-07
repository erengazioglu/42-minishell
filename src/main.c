/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/07 19:29:35 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static char	*get_input(void)
{
	char	*line;
	char	*trimmed;

	set_interactive_signals();
	line = readline("\e[0;36mminishell>\e[0m ");
	if (line == NULL)
		return (NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	trimmed = ft_strtrim(line, " \f\t\v\r\n");
	free(line);
	if (!trimmed)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr("exit\n", 2, -1, true);
		return (NULL);
	}
	return (trimmed);
}

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
 * @note `parse_input` frees input string.
 */
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void) argc;
	(void) argv;
	init_shell(&shell, envp);
	while (true)
	{
		input = get_input();
		if (!parse_input(&shell, input))
			break;
		if (shell.ast)
		{
			shell.last_exit_status = dispatch(&shell);
			free_ast(shell.ast);
		}
	}
	free_env(shell.env);
	rl_clear_history();
	return (0);
}
