/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:42:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/05 03:04:08 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

char	*ft_pathjoin(char *s1, char *s2)
{
	return (ft_strsjoin(s1, s2, '/', false));
}

char	**extract_paths(char *cmd, t_env *env)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = 0;
	while (env)
	{
		if (ft_str_startswith(env->key, "PATH", -1))
		{
			paths = ft_split(env->value, ':', false);
			break ;
		}
		env = env->next;
	}
	if (!paths)
		return (NULL);
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

int	get_exit_code(int exit_value)
{
	if (WIFSIGNALED(exit_value))
		return (128 + WTERMSIG(exit_value));
	if (WIFEXITED(exit_value))
		return (WEXITSTATUS(exit_value));
	return (1);
}
