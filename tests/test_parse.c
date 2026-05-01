/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:08:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/01 13:08:44 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief	Parser test. Reads tokens, turns them into AST, and prints them.
 */
void	test_parse(char *line, bool free_input)
{
	t_token	*root;
	t_ast	*ast;

	root = tokenize(line);
	printf("%sTokens:\n", YEL);
	print_tokens(root);
	ast = parse_tokens(root);
	printf("%sAST:\n", CYN);
	print_ast(ast);
	printf("%s", RST);
	free_ast(ast); // not done yet
	if (free_input)
		free(line);
}

int	main(int argc, char **argv)
{
	char	*input;

	input = ft_strunsplit(argv + 1, ' ', argc, false);
	if (!input)
		crash("unsplit argv failed");
	test_parse(input, false);
	return (0);
}
