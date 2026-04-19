/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:35:16 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/19 21:30:51 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

int	ft_cd(char **args, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!args || !args[0] || ft_strcmp(args[0], "cd") != 0)
		return (1);
	if (!args[1])
		return (ft_putstr_fd("cd: missing argument\n", 2), 1);
	if (args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (env)
		old_pwd = ft_get_old_pwd(*env);
	else
		old_pwd = ft_get_old_pwd(NULL);
	if (chdir(args[1]) != 0)
	{
		free(old_pwd);
		perror("cd");
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	ft_update_cd_env(env, old_pwd, new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
