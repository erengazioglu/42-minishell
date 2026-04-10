/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:34:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 17:03:01 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_tokenize(char *line, bool free_input)
{
	t_token	*root;

	ft_printf("start tokenize\n");
	root = tokenize(line);
	print_tokens(root);
	free_tokens(root);
	if (free_input)
		free(line);
}

int	main(int argc, char **argv)
{
	char	*input;

	input = ft_strunsplit(argv, ';', argc, false);
	test_tokenize(input, false);
	return (0);
}