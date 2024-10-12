/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:36:10 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 16:54:54 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ELF32.h"
# include "ELF64.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/stat.h>

typedef enum { false, true } bool;
# define true  1
# define false 0

typedef struct s_args
{
	bool	a_display_debug;
	bool	g_only_external;
	bool	u_only_undefined;
	bool	r_reverse;
	bool	p_dont_sort;
	int		files_size;
}   t_args;

/* elf_parser.c */
void	parse_elfs_list(t_list *files, t_args *args);
int		parse_elf(char *file, t_args *args);
int		get_elf_type(void *map, char *file);

/* file_utils.c */
int		open_file(char *file);
off_t	get_filesize(int fd);

/* parser.c */
t_list    *parse_args(char *arg, t_args *args);

#endif