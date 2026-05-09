/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:25:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/08 00:06:36 by egaziogl         ###   ########.fr       */
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

/**
 * @brief Apply pipe FDs and AST redirections for a command leaf.
 *
 * If @p fd is non-NULL, applies the provided pipe endpoints (fd[2] -> STDIN,
 * fd[1] -> STDOUT) and closes the originals after dup'ing.
 * Then expands and applies the redirection list stored on @p ast.
 *
 * @param ast   AST node expected to contain @c leaf.redirs.
 * @param fd    Optional array of FDs coming from the pipeline executor.
 * @param shell Shell context used for redirection expansion.
 * @return true on success, false on failure.
 */
bool	redirect(t_ast *ast, t_shell *shell, t_intlist **hdoc)
{
	t_redir	*redir;

	if (shell->fd[2] != STDIN_FILENO)
	{
		if (dup2(shell->fd[2], 0) == -1)
			return (false);
		close(shell->fd[2]);
	}
	if (shell->fd[1] != STDOUT_FILENO)
	{
		if (dup2(shell->fd[1], 1) == -1)
			return (false);
		close(shell->fd[1]);
	}
	redir = ast->leaf.redirs;
	expand_redirs(redir, shell);
	while (redir)
	{
		if (!open_file(redir->target->content, redir->type, hdoc))
			return (false);
		redir = redir->next;
	}
	return (true);
}
