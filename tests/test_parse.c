/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:08:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 13:16:16 by egaziogl         ###   ########.fr       */
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
	ast = parse_tokens(root);
	(void) ast;
	free_tokens(root);
	if (free_input)
		free(line);
}

int	main(int argc, char **argv)
{
	char	*input;

	print_args(argc, argv);
	input = ft_strunsplit(argv, ' ', argc, false);
	if (!input)
		crash("unsplit argv failed");
	test_parse(input, false);
	return (0);
}
