/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:49:35 by egaziogl          #+#    #+#             */
/*   Updated: 2026/05/13 21:54:25 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

/**
 * @brief Map a command name to a builtin identifier.
 * @param str Command name (e.g. "cd", "echo").
 * @return Builtin id (e.g. @c CD) or -1 if not a builtin.
 */
int	is_builtin(char *str)
{
	if (!str)
		return (-1);
	if (ft_str_equals(str, "cd"))
		return (CD);
	if (ft_str_equals(str, "echo"))
		return (ECHO);
	if (ft_str_equals(str, "env"))
		return (ENV);
	if (ft_str_equals(str, "exit"))
		return (EXIT);
	if (ft_str_equals(str, "export"))
		return (EXPORT);
	if (ft_str_equals(str, "pwd"))
		return (PWD);
	if (ft_str_equals(str, "unset"))
		return (UNSET);
	return (-1);
}
