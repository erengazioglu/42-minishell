/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:21:30 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 17:40:15 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parser.h"

/**
 * @brief	Expand test. Reads tokens, expands them, and prints the result.
 */
void	test_expand(char *line)
{
	t_token	*root;

	root = tokenize(line);
	print_tokens(root);
	ft_printf("--- After expansion ---\n");
	expand_tokens(root);
	print_tokens(root);
}

int	main(int argc, char **argv)
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
	test_expand(input);
	return (0);
}
