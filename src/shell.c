/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 18:03:20 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 18:14:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: return exit code or something useful
char	*get_input(void)
{
	char	*line;
	char	*trimmed;

	set_interactive_signals();
	line = readline("\e[0;36mminishell>\e[0m ");
	if (line == NULL)
		return (NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	trimmed = ft_strtrim(line, " \f\t\v\r\n");
	free(line);
	return (trimmed);
}

// TODO: return exit code or something useful
int	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_from_envp(envp);
	shell->last_exit_status = 0;
	return (0);
}