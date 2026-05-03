/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:10 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 11:21:37 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parser.h"

/**
 * @brief	Execve test. Reads tokens, turns them into AST, and executes.
 */
void	test_execve(char *line, char **envp)
{
	t_token	*root;
	t_ast	*ast;

	root = tokenize(line);
	ast = parse_tokens(root);
	print_ast(ast);
	if (ast->node.type == NODE_PIPE)
	{
		ft_printf("Pipes not supported in test_execve\n");
		return ;
	}
	else
		dispatch(ast, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc < 2)
	{
		ft_putstr("Usage: ./test_parse <args>", 2, -1, true);
		return (1);
	}
	input = ft_strunsplit(argv + 1, ' ', argc, false);
	if (!input)
		crash("unsplit argv failed");
	test_execve(input, envp);
	return (0);
}
