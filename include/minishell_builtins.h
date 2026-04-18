/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 23:18:33 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/04/18 19:29:07 by jalfaiat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "libft.h"


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}t_env;

void	ft_echo(char **args);
void	ft_exit(char **args, int last_exit_status);
int		ft_unset(char **args, t_env **env);
int		ft_export(char **args, t_env *env);
int		ft_env(char **args, t_env *env);
int		ft_pwd(char **args);


#endif
