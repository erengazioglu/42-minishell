/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 18:05:22 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispatch(t_ast *ast, char **envp)
{
	char	**argv;

	ft_printf("Dispatching AST...\n");
	// handle_redirects(ast);
	expand_tokens(ast->leaf.argv);
	argv = build_argv(ast->leaf.argv);
	ft_printf("Executing command: %s\n", argv[0]);
	if (ft_strchr(argv[0], '/', 0, 0))
		execve(argv[0], argv, envp);
	else
		execve(argv[0], argv, envp);
}
