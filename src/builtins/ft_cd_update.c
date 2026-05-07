/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/07 10:33:35 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

/**
 * @brief Update PWD/OLDPWD after a successful directory change.
 * @param env Environment list to update.
 * @param old_pwd Previous working directory (may be NULL).
 * @param new_pwd Current working directory (may be NULL).
 * @return 0 (for convenience).
 */
int	ft_update_cd_env(t_env **env, char *old_pwd, char *new_pwd)
{
	if (old_pwd && env)
		ft_set_env_value(env, "OLDPWD", old_pwd);
	if (new_pwd && env)
		ft_set_env_value(env, "PWD", new_pwd);
	return (0);
}
