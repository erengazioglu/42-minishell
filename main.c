/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:54:35 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/13 12:54:36 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

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
			printf("exit\n");
			break;
		}

		if (strlen(line) > 0)
			add_history(line);

		// ==========================================
		// [PLACEHOLDER] 2. TOKENIZATION & PARSING
		// ==========================================

		if (strncmp(line, "sleep", 5) == 0)
		{
			printf("Running command (sleep 5)...\n");
			printf("Try pressing Ctrl-C or Ctrl-\\ now!\n");

			pid = fork();
			if (pid == 0)
			{
				set_child_signals();

				sleep(5);
				printf("\nSleep finished without being killed.\n");
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
