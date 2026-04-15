/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:18:22 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:07:54 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Compares two integers, and returns the lesser value.
 * @param i1	First value to compare.
 * @param i2	Second value to compare.
 */
int	ft_min(int i1, int i2)
{
	if (i1 > i2)
		return (i2);
	return (i1);
}

/**
 * @brief	Compares two integers, and returns the greater value.
 * @param i1	First value to compare.
 * @param i2	Second value to compare.
 */
int	ft_max(int i1, int i2)
{
	if (i1 > i2)
		return (i1);
	return (i2);
}
