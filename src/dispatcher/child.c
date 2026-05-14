/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 02:36:05 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/14 00:12:09 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**child_setup(t_ast *ast, t_shell *shell, int *argc)
{
	set_child_signals();
	if (shell->fd[0] >= 0
		&& shell->fd[0] != shell->fd[1]
		&& shell->fd[0] != shell->fd[2])
	{
		close(shell->fd[0]);
		shell->fd[0] = -1;
	}
	if (!redirect(ast, shell))
		exit(redirect_error(ast, shell));
	return (build_argv(ast->leaf.argv, argc));
}

static void	execute_absolute(char **argv, char **envp, t_shell *shell)
{
	int			err;
	struct stat	path_stat;

	if (stat(argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr("minishell: ", 2, -1, false);
		ft_putstr(argv[0], 2, -1, false);
		ft_putstr(": Is a directory\n", 2, -1, false);
		crash_child(126, shell);
	}
	// free_ast(shell->ast, true);
	execve(argv[0], argv, envp);
	err = errno;
	ft_putstr("minishell: ", 2, -1, false);
	errno = err;
	perror(argv[0]);
	free(argv);
	free_strarr(envp);
	if (err == ENOENT)
		crash_child(127, shell);
	else
		crash_child(126, shell);
}

static void	execute_relative(char **argv, char **envp, t_shell *shell)
{
	char	**paths;
	int		i;

	paths = extract_paths(*argv, shell->env);
	if (paths && !check_paths(paths))
		paths = NULL;
	execve(argv[0], argv, envp);
	i = 0;
	if (paths)
	{
		while (paths[i])
			execve(paths[i++], argv, envp);
	}
	free_strarr(paths);
	ft_putstr("minishell: ", 2, -1, false);
	ft_putstr(argv[0], 2, -1, false);
	ft_putstr(": command not found\n", 2, -1, false);
	if (shell->fd[1] != STDOUT_FILENO)
		close(STDOUT_FILENO);
	if (shell->fd[2] != STDIN_FILENO)
		close(STDIN_FILENO);
}

void	child_process(t_ast *ast, t_shell *shell)
{
	int		argc;
	char	**argv;
	char	**envp;

	argv = child_setup(ast, shell, &argc);
	if (!argv || !argv[0])
		exit(empty_command(ast, shell));
	if (is_builtin(argv[0]) != -1)
	{
		free(argv);
		exit(exec_builtin(ast, shell, true));
	}
	envp = env_to_envp(shell->env);
	if (ft_strchr(argv[0], '/', 0, 0))
		execute_absolute(argv, envp, shell);
	else
		execute_relative(argv, envp, shell);
	free(argv);
	free_strarr(envp);
	free_ast(shell->ast, true);
	empty_shell(shell, false);
	exit(127);
}
