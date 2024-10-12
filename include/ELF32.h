/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ELF32.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:10:05 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 17:57:26 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF32_H
# define ELF32_H

# include <stdint.h>

// Documentation: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format

typedef struct	s_ELF32_header
{
	unsigned char	e_ident[16];
	uint16_t 		e_type;
	uint16_t 		e_machine;
	uint32_t 		e_version;
	uint32_t 		e_entry;
	uint32_t 		e_phoff;
	uint32_t 		e_shoff;
	uint32_t 		e_flags;
	uint16_t 		e_ehsize;
	uint16_t 		e_phentsize;
	uint16_t 		e_phnum;
	uint16_t 		e_shentsize;
	uint16_t 		e_shnum;
	uint16_t 		e_shstrndx;
}	t_ELF32_header;

typedef struct	s_ELF32_section_header
{
	uint32_t	sh_name;
	uint32_t	sh_type;
	uint32_t	sh_flags;
	uint32_t	sh_addr;
	uint32_t	sh_offset;
	uint32_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint32_t	sh_addralign;
	uint32_t	sh_entsize;
}	t_ELF32_section_header;

typedef struct s_ELF32_symbol
{
	uint32_t 		st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	uint16_t		st_shndx;
	uint32_t		st_value;
	uint32_t		st_size;
}	t_ELF32_symbol;

#endif