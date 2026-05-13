/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:25:51 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 20:03:43 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function for `open_file`.
 * Opens file for IN and HEREDOC redirect modes.
 * @return New file descriptor, or -1 upon error.
 */
static int	open_read_file(t_shell *shell, t_redir *redir)
{
	int	fd;

	if (shell->fd[2] != STDIN_FILENO)
	{
		close(shell->fd[2]);
	}
	if (redir->type == REDIR_HEREDOC)
	{
		fd = redir->fd;
		close(STDIN_FILENO);
		return (fd);
	}
	fd = open(redir->target->content, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2, -1, false);
		perror(redir->target->content);
		return (-1);
	}
	close(STDIN_FILENO);
	return (fd);
}

/**
 * @brief Helper function for `open_file`.
 * Opens file for APPEND and TRUNCATE redirect modes.
 * @return New file descriptor, or -1 upon error.
 */
static int	open_write_file(t_redir *redir)
{
	int	mode_flags;
	int	open_flags;
	int	fd;

	mode_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	open_flags = O_WRONLY | O_CREAT;
	if (redir->type == REDIR_APPEND)
		open_flags |= O_APPEND;
	else
		open_flags |= O_TRUNC;
	fd = open(redir->target->content, open_flags, mode_flags);
	if (fd == -1)
	{
		ft_putstr("minishell: ", 2, -1, false);
		perror(redir->target->content);
		return (-1);
	}
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
bool	open_file(t_shell *shell, t_redir *redir)
{
	int	fd_new;
	int	fd_keep;

	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
		fd_new = open_read_file(shell, redir);
	else
		fd_new = open_write_file(redir);
	if (fd_new == -1)
		return (false);
	fd_keep = dup2(fd_new, redir->type >= REDIR_APPEND);
	if (fd_keep == -1)
		return (false);
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
bool	redirect(t_ast *ast, t_shell *shell)
{
	t_redir	*redir;

	if (shell->fd[1] != STDOUT_FILENO)
	{
		if (dup2(shell->fd[1], 1) == -1)
			return (false);
		close(shell->fd[1]);
		shell->fd[1] = -1;
	}
	if (shell->fd[2] != STDIN_FILENO)
	{
		if (dup2(shell->fd[2], 0) == -1)
			return (false);
		close(shell->fd[2]);
		shell->fd[2] = -1;
	}
	redir = ast->leaf.redirs;
	expand_redirs(redir, shell);
	while (redir)
	{
		if (!open_file(shell, redir))
			return (false);
		redir = redir->next;
	}
	return (true);
}
