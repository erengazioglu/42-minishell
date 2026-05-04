/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:25:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/04 12:56:26 by egaziogl         ###   ########.fr       */
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
	t_redir	*redir;
	
	// --- HANDLE PIPES ---
	if (fd[2] != STDIN_FILENO)
	{
		if (dup2(fd[2], 0) == -1)
			return ; // TODO: handle dup2 error
		close(fd[2]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], 1) == -1)
			return ; // TODO: handle dup2 error
		close(fd[1]);
	}
	redir = ast->leaf.redirs;
	expand_redirs(redir);
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			ft_printf("> HEREDOC not implemented yet\n");
		else
			open_file(redir->target->content, redir->type);
		redir = redir->next;
	}
}
