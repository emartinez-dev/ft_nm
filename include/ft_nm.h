/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:36:10 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 21:45:54 by franmart         ###   ########.fr       */
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
int		parse_elfs_list(t_list *files);
int		parse_elf(char *file);
int		get_elf_type(void *map, char *file);
void	handle_elf(int elf_type, void *map);

/* elf64_handler.c */
void	handle_elf64(void *map);
void	read_symbols_elf64(t_ELF64_symbol *symtab, uint64_t n_sym, uint16_t n_sh,
							t_ELF64_section_header *sh, char *strtab);
void	print_elf64_symbol(t_ELF64_symbol *sym, uint16_t n_sh, t_ELF64_section_header *sh,
							char *strtab);
char    get_symbol_class_elf64(t_ELF64_symbol *sym, t_ELF64_section_header *sh);
t_ELF64_symbol	**sort_elf64_list(t_ELF64_symbol **list, uint64_t len, char *str_table);

/* elf32_handler.c */
void	handle_elf32(void *map);
void	read_symbols_elf32(t_ELF32_symbol *symtab, uint32_t n_sym, uint16_t n_sh,
							t_ELF32_section_header *sh, char *strtab);
void	print_elf32_symbol(t_ELF32_symbol *sym, uint16_t n_sh, t_ELF32_section_header *sh,
							char *strtab);
char    get_symbol_class_elf32(t_ELF32_symbol *sym, t_ELF32_section_header *sh);
t_ELF32_symbol	**sort_elf32_list(t_ELF32_symbol **list, uint64_t len, char *str_table);


/* file_utils.c */
int		open_file(char *file);
off_t	get_filesize(int fd);

/* parser.c */
t_list	*parse_args(char *arg);

/* output.c */
void    print_number_with_padding(uint64_t n, int width);

#endif