/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:34:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/10 13:36:53 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	bool	free_line;

	if (argc == 1)
		crash("invalid args");
	free_line = false;
	if (argc == 2)
		input = argv[1];
	else
	{
		input = ft_strunsplit(argv, ' ', false);
		free_line = true;
	}
	ft_printf("%s\n", input[0]);
	test_tokenize(input, free_line);
	return (0);
}