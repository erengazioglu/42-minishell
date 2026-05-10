/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/10 13:20:38 by jalfaiat         ###   ########.fr       */
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
		if (!isatty(fileno(stdin)))
			line = get_next_line(fileno(stdin));
		else if (minishell)
			line = readline("\e[0;36mminishell>\e[0m ");
		else
			line = readline("\e[0;36m>\e[0m ");
		if (!line)
			return (free(trimmed), NULL);
		if (isatty(fileno(stdin)) && ft_strlen(line) > 0)
			add_history(line);
		free(trimmed);
		trimmed = ft_strtrim(line, " \f\t\v\r\n");
		free(line);
		if (!trimmed)
			return (NULL);
	}
	return (trimmed);
}

static bool	unclosed_quotes(const char *str)
{
	int	in_sq;
	int	in_dq;

	in_sq = 0;
	in_dq = 0;
	while (*str)
	{
		if (*str == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (*str == '"' && !in_sq)
			in_dq = !in_dq;
		str++;
	}
	return (in_sq || in_dq);
}

static char	*prompt_close_quotes(t_shell *shell, char *input)
{
	char	*more;
	char	*joined;
	char	*err;

	err = "minishell: syntax error: unexpected EOF while looking for matching "
		"quote";

	while (unclosed_quotes(input))
	{
		more = prompt(false);
		if (!more)
		{
			free(input);
			crash_main(err, shell);
		}
		joined = ft_strsjoin(input, more, '\n', true);
		free(more);
		if (!joined)
			crash_main("minishell: malloc error", shell);
		input = joined;
	}
	return (input);
}

static char	*prompt_valid(t_shell *shell, bool minishell)
{
	char	*input;
	char	**check;

	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_main(NULL, shell);
		input = prompt_close_quotes(shell, input);
		check = ft_split_quotes(input);
		if (!check)
			crash_main("minishell: malloc error", shell);
		free_strarr(check);
		return (input);
	}
}

/**
 * @brief	Function to have shell prompt for user input, and tokenize.
 */
void	get_input(t_shell *shell)
{
	char	*input;

	set_interactive_signals();
	input = prompt_valid(shell, true);
	shell->tokens = tokenize(input, NULL);
	free(input);
	while (fetch_token(shell->tokens, -1)->type == TK_PIPE)
	{
		input = prompt_valid(shell, false);
		shell->tokens = tokenize(input, shell->tokens);
		free(input);
	}
}

/**
 * @brief Entry point for minishell. Gets input, parses it into an AST,
 * and calls `dispatch` when all conditions are met.
 * @param argc Unused.
 * @param argv Unused.
 * @param envp Environment array used to build the internal env list.
 * @return Always 0 (normal termination via EOF).
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
