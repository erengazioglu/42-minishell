/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:34:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/12 19:35:07 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief	Tokenize test. Turns any string into tokens that can be parsed.
 * Run these tests with args like "<", "|", 
 * "< Makefile cat -e | ls '$var' << EOF"...
 */
void	test_tokenize(char *line, bool free_input)
{
	t_token	*root;

	root = tokenize(line);
	print_tokens(root);
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
	test_tokenize(input, false);
	return (0);
}