/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:28 by franmart          #+#    #+#             */
/*   Updated: 2024/10/21 22:59:57 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int     number_width(uint64_t n);

void    print_number_with_padding(uint64_t n, int width)
{
	int	n_width = number_width(n);

	while (n_width < width)
	{
		ft_printf("0");
		n_width++;
	}
	ft_printf("%x ", n);
}

char    get_type_elf64(t_ELF64_symbol *sym, t_ELF64_section_header *section_h,
						char *shstrtab)
{
	char	class = '?';
	char	*section_name = &shstrtab[section_h[sym->st_shndx].sh_name];
	t_ELF64_section_header	*symbol_section = &section_h[sym->st_shndx];

	if (section_h[sym->st_shndx].sh_type == SHN_UNDEF)
	{
		class = 'U';
		if (ST_BIND(sym->st_info) == STB_WEAK)
			class = (ST_TYPE(sym->st_info) == STT_OBJECT) ? 'V' : 'w';
	}
	else if (section_h[sym->st_shndx].sh_type == SHN_ABS)
		class = 'A';
	else if (section_h[sym->st_shndx].sh_type == SHN_COMMON)
		class = 'C';
	else
	{
		if (ft_strncmp(section_name, ".text", 5) == 0 || ST_TYPE(sym->st_info) == STT_FUNC)
		{
			class = 'T';
			class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'T' : 't';
		}
		else if (ft_strncmp(section_name, ".bss", 4) == 0)
			class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'B' : 'b';
		else if (ft_strncmp(section_name, ".dynamic", 8) == 0)
			class = 'd';
		else if (ft_strncmp(section_name, ".data", 5) == 0 || symbol_section->sh_flags & SHF_WRITE)
		{
			if (ST_BIND(sym->st_info) == STB_WEAK)
				class = 'W';
			else
				class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'D' : 'd';
		}
		else if (symbol_section->sh_flags != SHF_WRITE)
			class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'R' : 'r';
	}
	return (class);
}

int     number_width(uint64_t n)
{
	int width = 0;

	if (n == 0)
		return (1);
	while (n != 0)
	{
		width++;
		n = n / 16;
	}
	return (width);
}

