/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:35:16 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 02:53:53 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include <stdio.h>

int	ft_cd(char **args, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!args || !args[0] || !ft_str_equals(args[0], "cd"))
		return (1);
	if (!args[1])
		return (ft_putstr("cd: missing argument", 2, -1, true), 1);
	if (args[1] && args[2])
	{
		ft_putstr("minishell: cd: too many arguments\n", 2, -1, false);
		return (2);
	}
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
