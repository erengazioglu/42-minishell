/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:34:00 by egaziogl          #+#    #+#             */
/*   Updated: 2026/04/07 16:10:33 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GNL_H
# define LIBFT_GNL_H

# include "libft_base.h"

# ifndef GNL_BUFSIZ
#  define GNL_BUFSIZ 64
# endif

char	*get_next_line(int fd);

#endif