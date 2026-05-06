/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:30:25 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/06 10:05:45 by egaziogl         ###   ########.fr       */
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
t_intlist	*create_heredoc(t_redir *redir)
{
	char	*input;
	int		fd[2];
	int		pid;
	int		status;

	ft_printf("> create_heredoc called\n");
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		while (true)
		{
			input = readline("> ");
			ft_printf("%s   %s%s\n", GRN, input, RST);
			if (ft_str_equals(input, redir->target->content))
				break;
			write(fd[1], input, ft_strlen(input));
			free(input);
		}
		free(input);
		close(fd[1]);
		exit(0);
	}
	wait(&status);
	// TODO: catch exit code in child, print error...
	return (new_int(fd[0]));
}

t_intlist	*create_heredocs(t_ast *ast)
{
	t_intlist	*hdoc;
	t_redir		*redir;

	ft_printf("> create_heredocs called\n");
	hdoc = NULL;
	while (ast->node.type == NODE_PIPE)
	{
		redir = ast->node.left->leaf.redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				append_int(&hdoc, create_heredoc(redir));
			redir = redir->next;
		}
		ast = ast->node.right;
	}
	redir = ast->leaf.redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			append_int(&hdoc, create_heredoc(redir));
		redir = redir->next;
	}
	return (hdoc);
}