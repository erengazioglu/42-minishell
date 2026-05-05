/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 17:48:16 by jalfaiat         ###   ########.fr       */
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
	t_env	*env;
	int		exit_code;

	(void)argc;
	(void)argv;
	env = env_from_envp(envp);
	exit_code = 0;
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
				exit_code = dispatch(ast, &env);
				free_ast(ast);
			}
		}
		free(line);
	}
	rl_clear_history();
	return (exit_code);
}
