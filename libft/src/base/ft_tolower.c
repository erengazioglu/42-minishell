/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:00:11 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/05 21:56:08 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Returns the lowercase version of the character.
 * @param c	Character to check.
 * @return	If the character is not alphabetical,
 * 			returns the same character back.
 */
int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		c += 32;
	return (c);
}
