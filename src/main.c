/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/15 18:21:13 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int main(void)
{
	char	*line;
	pid_t	pid;

	while (1)
	{
		set_interactive_signals();

		line = readline("minishell> ");
		if (line == NULL)
		{
			ft_putstr("exit\n", 2, -1, true);
			break;
		}
		if (ft_strlen(line) > 0)
			add_history(line);

		// ==========================================
		// [PLACEHOLDER] 2. TOKENIZATION & PARSING
		// ==========================================

		if (!ft_strncmp(line, "sleep", 5))
		{
			ft_printf("Running command (sleep 5)...\n");
			ft_printf("Try pressing Ctrl-C or Ctrl-\\ now!\n");

			pid = fork();
			if (pid == 0)
			{
				set_child_signals();
				sleep(5);
				ft_printf("\nSleep finished without being killed.\n");
				exit(0);
			}
			else if (pid > 0)
			{
				set_execution_signals();
				waitpid(pid, NULL, 0);
			}
		}

		free(line);
	}
	return (0);
}
