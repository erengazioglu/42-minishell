/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/30 16:13:36 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	main(void)
{
	char	*line;
	t_token	*tokens;

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
		if (tokens)
		{
			print_tokens(tokens);
			free_tokens(tokens);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
