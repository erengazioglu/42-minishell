/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 02:30:07 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 03:48:11 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Skips the initial dollar sign, reads until it's no longer a valid
 * variable name, and returns the name of the variable.
 * @param str	Pointer to the string starting with the dollar sign.
 * @note Advances the string pointer.
 */
char	*pick_var_name(char **str)
{
	int		i;
	char	*result;

	(*str)++;
	if (!(**str) || ft_isspace(**str))
		return (NULL);
	if (**str == '?')
	{
		(*str)++;
		return (ft_strdup("?"));
	}
	i = 0;
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	if (i == 0)
		return (NULL);
	result = ft_substr(*str, 0, i);
	*str += i;
	return (result);
}

char	*ft_getenv(t_shell *shell, char *key)
{
	t_env	*env;

	if (ft_str_equals(key, "?"))
		return (ft_itoa(shell->last_exit_status));
	env = shell->env;
	while (env)
	{
		if (env->key && ft_str_equals(env->key, key))
		{
			if (env->value)
				return (ft_strdup(env->value));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}
