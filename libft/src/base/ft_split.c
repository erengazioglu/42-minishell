/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:42:11 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 12:25:27 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/**
 * @brief	Frees a memory-allocated array of strings.
 * @param arr	Array to free.
 */
void	free_strarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	skip(char const *s, char c, bool is_word)
{
	int	i;

	i = 0;
	if (is_word)
	{
		while (s[i] && s[i] != c)
			i++;
	}
	else
	{
		while (s[i] && s[i] == c)
			i++;
	}
	return (i);
}

static int	count_words(char const *s, char c, bool ltrim)
{
	int	count;

	if (*s && ltrim)
		s += skip(s, c, false);
	if (!(*s))
		return (0);
	s += skip(s, c, false);
	s += skip(s, c, true);
	count = 1;
	while (*s)
	{
		s += skip(s, c, false);
		if (*s)
		{
			count++;
			s += skip(s, c, true);
		}
	}
	return (count);
}

static int	pick_word(char const *s, char c, char **result, bool ltrim)
{
	int	start;
	int	len;

	start = 0;
	if (ltrim)
		start += skip(s, c, false);
	len = start;
	while (s[len] && s[len] != c)
		len++;
	*result = ft_substr(s, start, len);
	return (len);
}

/**
 * @brief	Splits a string at every occurrence of a given delimiter,
 * 	and returns a pointer to the first string.
 * @param s	String to split.
 * @param c	Delimiter to split at.
 * @param ltrim	Option to trim the first word.
 * @return	A pointer to an array of null-terminated C strings.
 * @note	The return value is a memory-allocated, NULL-terminated
 * 	array of pointers. It must be protected and freed accordingly.
 */
char	**ft_split(char const *s, char c, bool ltrim)
{
	char	**result;
	char	**retval;

	result = ft_calloc(count_words(s, c, ltrim) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	retval = result;
	if (ltrim && *s)
		s += skip(s, c, false);
	if (!(*s))
		return (retval);
	while (*s)
	{
		s += pick_word(s, c, result, ltrim);
		if (!(*result))
			return (free_strarr(retval), NULL);
		result++;
		s += skip(s, c, false);
	}
	return (retval);
}
