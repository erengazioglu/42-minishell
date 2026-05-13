/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 11:48:29 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 23:12:37 by jalfaiat         ###   ########.fr       */
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
int	builtin_sorter(int builtin_id, char **argv, t_shell *shell)
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
		return (ft_exit(argv, shell->last_exit_status, shell));
	if (builtin_id == EXPORT)
		return (ft_export(argv, &shell->env));
	if (builtin_id == PWD)
		return (ft_pwd(argv));
	if (builtin_id == UNSET)
		return (ft_unset(argv, &shell->env));
	return (-1);
}

void	restore_fds(t_shell *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[3], STDOUT_FILENO);
	close(shell->fd[0]);
	close(shell->fd[3]);
}

int	exit_builtin(t_shell *shell, bool is_child, int exit_code)
{
	if (is_child)
	{
		if (shell->fd[1] != STDOUT_FILENO)
			close(STDOUT_FILENO);
		if (shell->fd[2] != STDIN_FILENO)
			close(STDIN_FILENO);
		empty_shell(shell);
		free_ast(shell->ast);
	}
	// else
	// 	restore_fds(shell);
	return (exit_code);
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
int	exec_builtin(t_ast *ast, t_shell *shell, bool is_child)
{
	int		argc;
	char	**argv;
	int		builtin_id;
	int		status;

	status = 0;
	if (!is_child)
	{
		// shell->fd[0] = dup(STDIN_FILENO);
		// shell->fd[3] = dup(STDOUT_FILENO);
		if (!redirect(ast, shell))
			return (exit_builtin(shell, is_child, 1));
	}
	argv = build_argv(ast->leaf.argv, &argc);
	if (!argv || !argv[0])
		return (free(argv), exit_builtin(shell, is_child, 0));
	builtin_id = is_builtin(argv[0]);
	status = builtin_sorter(builtin_id, argv, shell);
	return (free(argv), exit_builtin(shell, is_child, status));
}
