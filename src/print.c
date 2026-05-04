/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:54:40 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/01 16:29:07 by egaziogl         ###   ########.fr       */
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

void	print_cmd(t_ast *ast)
{
	t_token	*tkn;
	t_redir	*redir;

	ft_printf("CMD: argc=%d\n", ast->leaf.argc);
	tkn = ast->leaf.argv;
	while (tkn)
	{
		ft_printf("  - %s\n", tkn->content);
		tkn = tkn->next;
	}
	redir = ast->leaf.redirs;
	while (redir)
	{
		ft_printf("(redir %d) %s\n", redir->type, redir->target->content);
		redir = redir->next;
	}
}

void	print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	ft_printf("%s", CYN);
	if (ast->node.type == NODE_PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(ast->node.left);
		print_ast(ast->node.right);
	}
	else if (ast->node.type == NODE_CMD)
		print_cmd(ast);
	else if (ast->node.type == NODE_ERR)
		ft_printf("ERROR: %d\n", ast->err.err);
	ft_printf("%s", RST);
}
