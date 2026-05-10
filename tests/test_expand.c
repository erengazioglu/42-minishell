/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:21:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/09 20:47:54 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parser.h"

/**
 * @brief	Expand test. Reads tokens, expands them, and prints the result.
 */
void	test_expand(char *line, char **envp)
{
	t_shell	shell;
	t_token	*root;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_from_envp(envp);
	shell.last_exit_status = 0;
	root = tokenize(line, NULL);
	free(line);
	print_tokens(root);
	ft_printf("--- After expansion ---\n");
	expand_tokens(root, &shell);
	print_tokens(root);
	free_tokens(root);
	free_env(shell.env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc < 2)
	{
		ft_putstr("Usage: ./test_expand <args>", 2, -1, true);
		return (1);
	}
	input = ft_strunsplit(argv + 1, ' ', argc, false);
	if (!input)
		crash("unsplit argv failed");
	test_expand(input, envp);
	return (0);
}
