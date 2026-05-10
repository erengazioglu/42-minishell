/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:10 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/09 20:48:20 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parser.h"

/**
 * @brief	Execve test. Reads tokens, turns them into AST, and executes.
 */
void	test_execve(char *line, char **envp)
{
	t_shell	shell;

	if (!init_shell(&shell, envp))
		crash_main("minishell: malloc error", NULL);
	if (!parse_input(&shell, line))
	{
		empty_shell(&shell);
		return ;
	}
	print_ast(shell.ast);
	shell.last_exit_status = dispatch(&shell);
	free_ast(shell.ast);
	cleanup(&shell);
	empty_shell(&shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc < 2)
	{
		ft_putstr("Usage: ./test_execve <args>", 2, -1, true);
		return (1);
	}
	input = ft_strunsplit(argv + 1, ' ', argc, false);
	if (!input)
		crash("unsplit argv failed");
	test_execve(input, envp);
	return (0);
}
