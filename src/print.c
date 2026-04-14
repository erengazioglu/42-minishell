/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:54:40 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/12 19:19:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_args(int argc, char **argv)
{
	int	i;

	i = 1;
	ft_printf("%s%d args:\n(0) %s", YEL, argc, argv[0]);
	while (i < argc)
	{
		ft_printf("\n(%d) %s", i, argv[i]);
		i++;
	}
	ft_printf("%s\n", RST);
}

void	print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->node.type == NODE_PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(ast->node.left);
		print_ast(ast->node.right);
	}
	else if (ast->node.type == NODE_CMD)
	{
		ft_printf("CMD: argc=%d\n", ast->leaf.argc);
		t_token *tkn = ast->leaf.argv;
		while (tkn)
		{
			ft_printf("  - %s\n", tkn->content);
			tkn = tkn->next;
		}
		t_redir *redir = ast->leaf.redirs;
		while (redir)
		{
			ft_printf("  > %s\n", redir->target->content);
			redir = redir->next;
		}
	}
	else if (ast->node.type == NODE_ERR)
		ft_printf("ERROR: %d\n", ast->err.err);
}
