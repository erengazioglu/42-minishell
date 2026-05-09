/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/09 12:31:52 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/**
 * @brief Prompts user for an input, and keeps going until the trimmed input
 * is not an empty string.
 * @param minishell	Option to print "minishell" or not (`false` when waiting
 * for additional input.)
 * @return	Non-empty string, or `NULL` on failure.
 */
static char	*prompt(bool minishell)
{
	char	*line;
	char	*trimmed;

	trimmed = ft_strdup("");
	while (!*trimmed)
	{
		if (minishell)
			line = readline("\e[0;36mminishell>\e[0m ");
		else
			line = readline("\e[0;36m>\e[0m ");
		if (line == NULL)
			return (free(trimmed), NULL);
		if (ft_strlen(line) > 0)
			add_history(line);
		free(trimmed);
		trimmed = ft_strtrim(line, " \f\t\v\r\n");
		free(line);
		if (!trimmed)
			return (NULL);
	}
	return (trimmed);
}

/**
 * @brief	Function to have shell prompt for user input, and tokenize.
 */
void	get_input(t_shell *shell)
{
	char	*input;

	set_interactive_signals();
	input = prompt(true);
	if (!input)
		crash_main(NULL, shell);
	shell->tokens = tokenize(input, NULL);
	free(input);
	while (fetch_token(shell->tokens, -1)->type == TK_PIPE)
	{
		input = prompt(false);
		if (!input)
			crash_main("minishell: syntax error: unexpected end of file", shell);
		shell->tokens = tokenize(input, shell->tokens);
	}
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
	t_shell	shell;

	(void) argc;
	(void) argv;
	if (!init_shell(&shell, envp))
		crash_main("minishell: malloc error", NULL);
	while (true)
	{
		get_input(&shell);
		shell.ast = parse_tokens(shell.tokens);
		if (shell.ast)
		{
			shell.last_exit_status = dispatch(&shell);
			free_ast(shell.ast);
		}
		cleanup(&shell);
	}
	empty_shell(&shell);
	return (0);
}
