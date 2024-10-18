/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ELF64.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:15:26 by franmart          #+#    #+#             */
/*   Updated: 2024/10/18 16:54:04 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF64_H
# define ELF64_H

# include <stdint.h>

// Documentation: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format

typedef struct	s_ELF64_header
{
	unsigned char	e_ident[16];
	uint16_t 		e_type;
	uint16_t 		e_machine;
	uint32_t 		e_version;
	uint64_t 		e_entry;
	uint64_t 		e_phoff;
	uint64_t 		e_shoff;
	uint32_t 		e_flags;
	uint16_t 		e_ehsize;
	uint16_t 		e_phentsize;
	uint16_t 		e_phnum;
	uint16_t 		e_shentsize;
	uint16_t 		e_shnum;
	uint16_t 		e_shstrndx;
}	t_ELF64_header;

typedef struct	s_ELF64_section_header
{
	uint32_t	sh_name;
	uint32_t	sh_type;
	uint64_t	sh_flags;
	uint64_t	sh_addr;
	uint64_t	sh_offset;
	uint64_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint64_t	sh_addralign;
	uint64_t	sh_entsize;
}	t_ELF64_section_header;

// Symbol docs: https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-79797/index.html

typedef struct s_ELF64_symbol
{
	uint32_t 		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	uint16_t		st_shndx;
	uint64_t		st_value;
	uint64_t		st_size;
}	t_ELF64_symbol;

#endif