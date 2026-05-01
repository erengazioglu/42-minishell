/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/01 11:46:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

	while (1)
	{
		set_interactive_signals();
		line = readline("minishell> ");
		if (line == NULL)
		{
			ft_putstr("exit\n", 2, -1, true);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		tokens = tokenize(line);
		printf("%sTokens:\n", YEL);
		print_tokens(tokens);
		ast = parse_tokens(tokens);
		printf("%sAST:\n", CYN);
		print_ast(ast);
		printf("%s", RST);
		free_ast(ast); // not done yet
		free(line);
	}
	rl_clear_history();
	return (0);
}
