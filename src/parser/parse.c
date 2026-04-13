/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:25:04 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/13 13:19:39 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell_parser.h"
#include "../../include/minishell_tokenizer.h"

int	find_node(t_token *root)
{
	int	i;

	i = 0;
	while (root)
	{
		if (root->type == TK_PIPE)
			return (i);
		root = root->next;
		i++;
	}
	return (-1);
}

t_ast	*parse_tokens(t_token *root)
{
	int	i;

	i = find_node(root);
	if (i == -1)
		ft_printf("there's no pipe\n");
	else
		ft_printf("there's a pipe at idx %d\n", i);
	return (NULL);
}