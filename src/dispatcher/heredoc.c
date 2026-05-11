/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:30:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/11 19:49:44 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_intlist	*new_int(int val)
{
	t_intlist	*il;
	
	il = malloc(sizeof(t_intlist));
	if (!il)
		return (NULL);
	il->next = NULL;
	il->val = val;
	return (il);
}

/**
 * @brief Appends an int to the end of a redirection list.
 * @param root	Pointer to the first element of the redirection list. 
 * If `*root` is `NULL`, the new redir becomes the first element.
 * @param new	Redirection to append.
 */
void	append_int(t_intlist **root, t_intlist *new)
{
	t_intlist	*temp;

	if (!new)
		return ;
	if (!*root)
	{
		*root = new;
		return ;
	}
	temp = *root;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

/**
 * @brief Creates a pipe, displays the heredoc prompt, writes input into
 * the pipe, closes the write end, and returns the read end as a linked list.
 * @param redir	Redir object.
 */
t_intlist	*create_heredoc(t_shell *shell, t_redir *redir)
{
	char	*input;
	int		fd[2];
	int		pid;
	int		status;
	int		i;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		free_intlist(shell->hdoc, true);
		i = 1;
		while (true)
		{
			input = readline("> ");
			if (!input)
			{
				ft_putstr("minishell: warning: here-document at line ", 2, -1, false);
				ft_putnbr(i, 2, false);
				ft_putstr(" delimited by end of file (wanted '", 2, -1, false);
				ft_putstr(redir->target->content, 2, -1, false);
				ft_putstr("')", 2, -1, true);
				break;
			}
			if (ft_str_equals(input, redir->target->content))
				break;
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
			free(input);
			i++;
		}
		free(input);
		close(fd[1]);
		free_ast(shell->ast);
		free_env(shell->env);
		exit(0);
	}
	close(fd[1]);
	wait(&status);
	// TODO: catch exit code in child, print error...
	return (new_int(fd[0]));
}

t_intlist	*create_heredocs(t_shell *shell)
{
	t_redir		*redir;
	t_ast		*ast;

	ast = shell->ast;
	while (ast->node.type == NODE_PIPE)
	{
		redir = ast->node.left->leaf.redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				append_int(&(shell->hdoc), create_heredoc(shell, redir));
			redir = redir->next;
		}
		ast = ast->node.right;
	}
	redir = ast->leaf.redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			append_int(&(shell->hdoc), create_heredoc(shell,redir));
		redir = redir->next;
	}
	return (shell->hdoc);
}
