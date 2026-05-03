/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:25:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 23:25:38 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	redirect(t_state *state, int n)
// {
// 	int	fd;

// 	if (n == 1)
// 	{
// 		open_file(state, FLAG_READ);
// 		fd = dup_fd(state, state->fd[1], 1);
// 		close_fds(state, false);
// 		return ;
// 	}
// 	else if (n < state->argc - 3)
// 	{
// 		fd = dup_fd(state, state->fd[2], 0);
// 		fd = dup_fd(state, state->fd[1], 1);
// 		close_fds(state, true);
// 		return ;
// 	}
// 	fd = dup_fd(state, state->fd[2], 0);
// 	close(state->fd[2]);
// 	open_file(state, FLAG_WRITE);
// }

void	redirect(t_ast *ast, int *fd)
{
	(void) fd;
	ft_printf(">\tHandling redirects...\n");
	expand_redirs(ast->leaf.redirs);
	print_ast(ast);
}
