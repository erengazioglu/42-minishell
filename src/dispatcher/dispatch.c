/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:15:37 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/03 21:23:38 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_ast *ast, char **envp, int *fd)
{
	int		argc;
	char	**argv;
	char	**paths;
	int		i;

	handle_redirects(ast, fd);
	expand_tokens(ast->leaf.argv);
	argv = build_argv(ast->leaf.argv, &argc);
	if (ft_strchr(argv[0], '/', 0, 0))
	{
		ft_printf("Executing command: %s\n", argv[0]);
		execve(argv[0], argv, envp);
		ft_putstr("something went wrong", 2, -1, true);
		return ;
	}
	paths = extract_paths(*argv, envp);
	check_paths(paths);
	execve(argv[0], argv, envp);
	i = 0;
	while (paths[i])
		execve(paths[i++], argv, envp);
	free_strarr(paths);
	ft_putstr("something went wrong", 2, -1, true);
}
// returns false if it fails
bool	create_pipe(int *fd)
{
	int	new_fd[2];

	if (pipe(new_fd) == -1)
		return (false);
	fd[0] = new_fd[0];
	fd[1] = new_fd[1];
	return (true);
}

void	dispatch(t_ast *ast, char **envp)
{
	int		fd[3];

	ft_printf("Dispatching AST...\n");
	while (ast->node.type == NODE_PIPE)
	{
		ft_printf("Pipes not supported in dispatch yet\n");
		ast = ast->node.right;
	}
	child_process(ast, envp, fd);
}
