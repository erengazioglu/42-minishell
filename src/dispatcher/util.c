/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:42:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/04 12:56:12 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char *s1, char *s2)
{
	return (ft_strsjoin(s1, s2, '/', false));
}

char	**extract_paths(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_str_startswith(envp[i], "PATH=", -1))
		{
			paths = ft_split(envp[i] + 5, ':', false);
			break ;
		}
		i++;
		if (!envp[i])
			return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_pathjoin(paths[i], cmd);
		if (!paths[i])
			return (NULL);
		i++;
	}
	return (paths);
}

/**
 * @brief Given a linked list of tokens, creates an array of strings
 * representing the arguments passed to the program.
 * @param root	First element of token list.
 * @param argc	Pointer to an integer to store `argc` in.
 * @return	Array of strings representing `argv`.
 * @note Does not free or clone anything, take care to not free the tokens
 * too early.
 */
char	**build_argv(t_token *root, int *argc)
{
	int		i;
	int		count;
	char	**argv;
	t_token	*curr;

	count = 0;
	curr = root;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i++] = root->content;
		root = root->next;
	}
	*argc = count;
	return (argv[i] = NULL, argv);
}

/**
 * @brief	Opens a file and redirects to STDIN or STDOUT.
 * @param fn	Name of the file to be opened.
 * @param flag	Type of redirect to handle.
 * @return		`true` on success, `false` on failure.
 * @note	Called by the child process. Call `exit()` freely on failure.
 */
bool	open_file(char *fn, t_redirtype flag)
{
	int	fd_new;
	int	fd_keep;

	if (flag == REDIR_IN)
	{
		close(STDIN_FILENO);
		fd_new = open(fn, O_RDONLY);
		if (fd_new == -1)
			return (false); // TODO: handle OPENR error
	}
	else
	{
		close(STDOUT_FILENO);
		fd_new = open(fn, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd_new == -1)
			return (false); // TODO: handle OPENW error
	}
	fd_keep = dup2(fd_new, flag >= REDIR_APPEND);
	if (fd_keep == -1)
		return (false); // TODO: handle DUP2 error
	close(fd_new);
	return (true);
}

int	get_exit_code(int exit_value)
{
	if (WIFSIGNALED(exit_value))
		return (128 + WTERMSIG(exit_value));
	if (WIFEXITED(exit_value))
		return (WEXITSTATUS(exit_value));
	return (1);
}
