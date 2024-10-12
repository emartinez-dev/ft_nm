/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:36:10 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 15:25:47 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ELF32.h"
# include "ELF64.h"

typedef enum { false, true } bool;
# define true  1
# define false 0

typedef struct s_args
{
	bool a_display_debug;
	bool g_only_external;
	bool u_only_undefined;
	bool r_reverse;
	bool p_dont_sort;
}   t_args;

/* parser.c */
t_list    *parse_args(char *arg, t_args *args);

#endif