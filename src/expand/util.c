/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:36:38 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 22:27:06 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Slices a portion of the string, returns the slice,
 * and updates the string pointer to the remaining part.
 * @param str Pointer to the original string. It will be freed and replaced
 * by the remaining part after slicing.
 * @param start Starting index of the slice.
 * @param len Length of the slice.
 * @return Newly allocated slice of the string, or NULL on failure.
 * @note Handles the memory management. You insert 1 memory-allocated string,
 * get 1 memory-allocated slice, and the original string is updated.
 */
char	*ft_strslice(char **str, int start, int len)
{
	char	*slice;
	char	*src;

	if (!str)
		return (NULL);
	slice = ft_substr(*str, start, len);
	if (!slice)
		return (NULL);
	src = *str;
	*str = ft_strdup(src + start + len);
	free(src);
	return (slice);
}

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
