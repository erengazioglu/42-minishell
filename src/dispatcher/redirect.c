/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:25:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/06 12:23:44 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for `open_file`.
 * Opens file for IN and HEREDOC redirect modes.
 * @return New file descriptor, or -1 upon error.
 * @todo HEREDOC isn't implemented yet. Call its function from here.
 * @note You could have this function handle errors too?
 */
int	open_read_file(char *fn, t_redirtype mode, t_intlist **hdoc)
{
	int	fd;
	t_intlist	*temp;

	if (mode == REDIR_HEREDOC)
	{
		fd = (*hdoc)->val;
		close(STDIN_FILENO);
		temp = *hdoc;
		*hdoc = (*hdoc)->next;
		free(temp);
		return (fd);
	}
	fd = open(fn, O_RDONLY);
	close(STDIN_FILENO);
	return (fd);
}

/**
 * @brief Helper function for `open_file`.
 * Opens file for APPEND and TRUNCATE redirect modes.
 * @return New file descriptor, or -1 upon error.
 * @note You could have this function handle errors too?
 */
int	open_write_file(char *fn, t_redirtype mode)
{
	int	mode_flags;
	int	open_flags;
	int	fd;

	mode_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	open_flags = O_WRONLY | O_CREAT;
	if (mode == REDIR_APPEND)
		open_flags |= O_APPEND;
	else
		open_flags |= O_TRUNC;
	fd = open(fn, open_flags, mode_flags);
	close(STDOUT_FILENO);
	return (fd);
}

/**
 * @brief	Opens a file and redirects to STDIN or STDOUT.
 * @param fn	Name of the file to be opened.
 * @param mode	Type of redirect to handle.
 * @return		`true` on success, `false` on failure.
 * @note	Called by the child process. Call `exit()` freely on failure.
 */
bool	open_file(char *fn, t_redirtype mode, t_intlist **hdoc)
{
	int	fd_new;
	int	fd_keep;

	if (mode == REDIR_IN || mode == REDIR_HEREDOC)
	{
		fd_new = open_read_file(fn, mode, hdoc);
		if (fd_new == -1)
			return (false); // TODO: handle OPENR error
	}
	else
	{
		fd_new = open_write_file(fn, mode);
		if (fd_new == -1)
			return (false); // TODO: handle OPENW error
	}
	fd_keep = dup2(fd_new, mode >= REDIR_APPEND);
	if (fd_keep == -1)
		return (false); // TODO: handle DUP2 error
	close(fd_new);
	return (true);
}

void	redirect(t_ast *ast, int *fd, t_intlist **hdoc)
{
	t_redir	*redir;

	if (fd[2] != STDIN_FILENO)
	{
		if (dup2(fd[2], 0) == -1)
			return; // TODO: handle dup2 error
		close(fd[2]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], 1) == -1)
			return; // TODO: handle dup2 error
		close(fd[1]);
	}
	redir = ast->leaf.redirs;
	expand_redirs(redir);
	while (redir)
	{
		open_file(redir->target->content, redir->type, hdoc);
		redir = redir->next;
	}
}
