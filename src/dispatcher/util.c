/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:42:57 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/12 02:37:22 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

static int	count_args(t_token *root)
{
	int	count;

	count = 0;
	while (root)
	{
		if (root->type != TK_WORD || root->content[0] != '\0')
			count++;
		root = root->next;
	}
	return (count);
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
	char	**argv;

	*argc = count_args(root);
	if (*argc == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (*argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (root)
	{
		if (root->type != TK_WORD || root->content[0] != '\0')
			argv[i++] = root->content;
		root = root->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	get_exit_code(int exit_value)
{
	if (WIFSIGNALED(exit_value))
		return (128 + WTERMSIG(exit_value));
	if (WIFEXITED(exit_value))
		return (WEXITSTATUS(exit_value));
	return (1);
}

int	empty_command(t_ast *ast, t_shell *shell)
{
	free_ast(ast);
	free_env(shell->env);
	exit(0);
}

int	redirect_error(t_ast *ast, t_shell *shell)
{
	(void) ast;
	free_ast(shell->ast);
	free_env(shell->env);
	exit(1);
}
