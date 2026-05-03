/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 11:28:25 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispatch(t_ast *ast, char **envp)
{
	(void) envp;
	ft_printf("Dispatching AST...\n");
	handle_redirects(ast);
}
