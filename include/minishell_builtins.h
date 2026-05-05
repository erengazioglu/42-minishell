/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalfaiat <jalfaiat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 23:18:33 by jalfaiat          #+#    #+#             */
/*   Updated: 2026/05/05 02:50:39 by jalfaiat         ###   ########.fr       */
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

typedef enum e_builtin_type
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}t_builtin_type;

/* ft_cd.c */
int		ft_cd(char **args, t_env **env);

/* ft_cd_utils.c */
char	*ft_get_old_pwd(t_env *env);
int		ft_set_env_value(t_env **env, char *key, char *value);

/* ft_cd_update.c */
int		ft_update_cd_env(t_env **env, char *old_pwd, char *new_pwd);

/* ft_echo.c */
void	ft_echo(char **args);

/* ft_env.c */
int		ft_env(char **args, t_env *env);
t_env	*env_from_envp(char **envp);
char	**env_to_envp(t_env *env);

/* ft_exit.c */
void	ft_exit(char **args, int last_exit_status);

/* ft_export.c */
int		ft_export(char **args, t_env **env);

/* ft_export_utils.c */
int		ft_export_process_arg(char *arg, t_env **env);

/* ft_pwd.c */
int		ft_pwd(char **args);

/* ft_unset.c */
int		ft_unset(char **args, t_env **env);

#endif
