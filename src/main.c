/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 18:26:11 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;
	char	*temp;

	(void) argc;
	(void) argv;
	while (1)
	{
		set_interactive_signals();
		line = readline("minishell> ");
		if (line == NULL)
		{
			if(isatty(STDIN_FILENO))
				ft_putstr("exit\n", 2, -1, true);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if (*temp)
		{
			tokens = tokenize(line);
			// print_tokens(tokens);
			ast = parse_tokens(tokens);
			if (ast)
			{
				// print_ast(ast);
				dispatch(ast, envp);
				free_ast(ast);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
