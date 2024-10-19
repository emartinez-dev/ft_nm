/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:36:10 by franmart          #+#    #+#             */
/*   Updated: 2024/10/19 13:37:59 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ELF.h"
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

/* elf_parser.c */
void	parse_elfs_list(t_list *files);
int		parse_elf(char *file);
int		get_elf_type(void *map, char *file);
void	handle_elf(int elf_type, void *map);

/* elf64_handler.c */
void			handle_elf64(void *map);
void			read_symbols_elf64(t_ELF64_symbol *symbol_table, uint64_t n_symbols,
							char *str_table, t_ELF64_section_header *section_h, char *shstrtab);
t_ELF64_symbol	**sort_elf64_list(t_ELF64_symbol **list, uint64_t len, char *str_table);
void			print_elf64_symbol(t_ELF64_symbol *sym, char *str_table,
							t_ELF64_section_header *section_h, char * shstrtab);

/* file_utils.c */
int		open_file(char *file);
off_t	get_filesize(int fd);

/* parser.c */
t_list    *parse_args(char *arg);

/* output.c */
void    print_number_with_padding(uint64_t n, int width);
char    get_type_elf64(t_ELF64_symbol *sym, t_ELF64_section_header *section_h,
						char *shstrtab);

#endif