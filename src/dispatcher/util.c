/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:42:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 17:56:51 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char *s1, char *s2)
{
	return (ft_strsjoin(s1, s2, '/', false));
}

/**
 * @brief Given a linked list of tokens, creates an array of strings
 * representing the arguments passed to the program.
 * @param root	First element of token list.
 * @return	Array of strings representing `argv`.
 * @note Does not free or clone anything, take care to not free the tokens
 * too early.
 */
char	**build_argv(t_token *root)
{
	int		i;
	int		argc;
	char	**argv;
	t_token	*curr;

	argc = 0;
	curr = root;
	while (curr)
	{
		argc++;
		curr = curr->next;
	}
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		argv[i++] = root->content;
		root = root->next;
	}
	return (argv[i] = NULL, argv);
}
