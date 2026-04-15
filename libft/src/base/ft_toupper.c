/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:57:26 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/05 21:57:26 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Returns the uppercase version of the character.
 * @param c	Character to check.
 * @return	If the character is not alphabetical,
 * 			returns the same character back.
 */
int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
		c -= 32;
	return (c);
}
