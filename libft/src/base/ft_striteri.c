/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:24 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/06 18:51:10 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Iterates on a string, calling a function for each char value in it.
 * @param s		String to iterate on.
 * @param f		Function to call for each character (takes an index and
 * a pointer as parameters).
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &(s[i]));
		i++;
	}
}
