/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:30:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 00:25:13 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Displays the heredoc prompt, writes input into the given file descriptor
 * until the stop word is encountered, and closes the file descriptor.
 * @param fd		File descriptor to write input into.
 * @param stop		Word that signals the end of input when encountered.
 * @note	Writes an error message on CTRL-D input.
 * @note	Closes the file descriptors.
 */
void	write_heredoc_input(int *fd, char *stop)
{
	char	*input;
	int		i;

	close(fd[0]);
	i = 1;
	while (true)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr("minishell: warning: here-document at line ", 2, -1, false);
			ft_putnbr(i, 2, false);
			ft_putstr(" delimited by end of file (wanted '", 2, -1, false);
			ft_putstr(stop, 2, -1, false);
			ft_putstr("')", 2, -1, true);
			break;
		}
		if (ft_str_equals(input, stop))
			break;
		ft_putstr(input, fd[1], -1, true);
		free(input);
		i++;
	}
	close(fd[1]);
	free(input);
}

/**
 * @brief Creates a pipe, displays the heredoc prompt, writes input into
 * the pipe, closes the write end, and returns the read end as a linked list.
 * @param redir	Redir object.
 * @return Read end file descriptor.
 */
int	create_heredoc(t_shell *shell, t_redir *redir, int *fd)
{
	int		pid;

	// if (fd[0] >= 0)
	// {
	// 	close(fd[0]);
	// 	fd[0] = -1;
	// }
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		write_heredoc_input(fd, redir->target->content);
		free_ast(shell->ast);
		free_env(shell->env);
		exit(0);
	}
	close(fd[1]);
	wait(NULL);
	return (fd[0]);
}

void	create_heredocs(t_shell *shell)
{
	t_redir		*redir;
	t_ast		*ast;
	int			fd[2];

	fd[0] = -1;
	fd[1] = -1;
	ast = shell->ast;
	while (ast->node.type == NODE_PIPE)
	{
		redir = ast->node.left->leaf.redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				redir->fd = create_heredoc(shell, redir, fd);
			redir = redir->next;
		}
		ast = ast->node.right;
	}
	redir = ast->leaf.redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			redir->fd = create_heredoc(shell, redir, fd);
		redir = redir->next;
	}
}
