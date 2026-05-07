/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:48:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/07 11:06:42 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validate that all candidate paths exist and are executable.
 *
 * On failure, frees the @p paths array via free_strarr(). On success, the
 * caller keeps ownership of @p paths.
 *
 * @param paths NULL-terminated array of candidate executable paths.
 * @return true if all entries exist and are executable, false otherwise.
 */
bool	check_paths(char **paths)
{
	int	result;
	int	i;

	result = -1;
	i = 0;
	while (paths[i] && result)
		result &= access(paths[i++], F_OK);
	if (result == -1)
		return (free_strarr(paths), false);
	result = -1;
	i = 0;
	while (paths[i] && result)
		result &= access(paths[i++], X_OK);
	if (result == -1)
		return (free_strarr(paths), false);
	return (true);
}

/**
 * @brief Execute the selected builtin implementation.
 * @param builtin_id Builtin identifier returned by is_builtin().
 * @param argv Argument vector (argv[0] is the builtin name).
 * @param shell Shell context (env + last status).
 * @return Builtin exit status.
 */
int builtin_sorter(int builtin_id, char **argv, t_shell *shell)
{
	if (builtin_id == CD)
		return (ft_cd(argv, &shell->env));
	if (builtin_id == ECHO)
	{
		ft_echo(argv);
		return (0);
	}
	if (builtin_id == ENV)
		return (ft_env(argv, shell->env));
	if (builtin_id == EXIT)
		return (ft_exit(argv, shell->last_exit_status));
	if (builtin_id == EXPORT)
		return (ft_export(argv, &shell->env));
	if (builtin_id == PWD)
		return (ft_pwd(argv));
	if (builtin_id == UNSET)
		return (ft_unset(argv, &shell->env));
	return (-1);
}

/**
 * @brief Execute a builtin in the parent process.
 *
 * Saves STDIN/STDOUT, applies redirections, expands tokens, builds argv and
 * runs the builtin. Restores STDIN/STDOUT before returning.
 *
 * @param ast Command AST leaf.
 * @param shell Shell context (env + last status).
 * @return Builtin exit status.
 */
int	exec_builtin(t_ast *ast, t_shell *shell)
{
	int		argc;
	char	**argv;
	int		builtin_id;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!redirect(ast, NULL, shell))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (ast->leaf.argv)
		expand_tokens(ast->leaf.argv, shell);
	argv = build_argv(ast->leaf.argv, &argc);
	if (!argv || !argv[0])
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (free(argv), 0);
	}
	builtin_id = is_builtin(argv[0]);
	status = builtin_sorter(builtin_id, argv, shell);
	free(argv);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}
