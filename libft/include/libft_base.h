/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_base.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:41:41 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/09 19:07:29 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BASE_H
# define LIBFT_BASE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <errno.h>

// ANSI text defines

# define RST "\e[0m"
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

// memory functions

void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	free_strarr(char **arr);

// int checks

int		ft_min(int i1, int i2);
int		ft_max(int i1, int i2);

// char checks & manipulations

bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);
bool	ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// write

void	ft_putchar(char c, int fd, bool newline);
void	ft_putnbr(int n, int fd, bool newline);
int		ft_putstr(char *s, int fd, int n, bool newline);

// string checks

size_t	ft_strlen(const char *s);
bool	ft_str_startswith(char *str, char *test, int n);
bool	ft_str_endswith(char *str, char *test, int n);
bool	ft_str_equals(char *str, char *test);
bool	ft_str_isnum(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strfind(const char *s, char c, int n, bool reverse);
char	*ft_strchr(const char *s, char c, int n, bool reverse);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_get_filename(char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

// string manipulation (operates on existing strings)

void	ft_strcat(char *dst, const char *src);
char	*ft_strcpy(char *dst, char *src, char delim, char end);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

// string generation (returns new strings)

char	*ft_strdup(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char *s1, char *s2, ssize_t n, bool free_s1);
char	*ft_strsjoin(char *s1, char *s2, char sep, bool free_s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strunsplit(char **arr, char sep, bool free_arr);
char	**ft_split(char const *s, char c, bool ltrim);

// int<->str conversions

char	*ft_itoa(int n);
char	*ft_itoa_base(unsigned long n, char *base);
char	*ft_itoa_uint(unsigned int n);
int		ft_atoi(const char *str);
int		ft_satoi(const char *str);

#endif