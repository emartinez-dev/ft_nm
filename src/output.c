/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:28 by franmart          #+#    #+#             */
/*   Updated: 2024/10/19 13:56:02 by franmart         ###   ########.fr       */
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
		if (ft_strncmp(section_name, ".text", 5) == 0)
		{
			class = 'T';
			class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'T' : 't';
		}
		else if (ft_strncmp(section_name, ".bss", 4) == 0)
			class = (ST_BIND(sym->st_info) == STB_GLOBAL) ? 'B' : 'b';
		else if (ft_strncmp(section_name, ".rodata", 7) == 0)
			class = 'R';
		else if (ft_strncmp(section_name, ".data", 5) == 0)
			class = 'D';
	}
	/* TODO: Implement these types
	./ft_nm ft_nm > a ; LC_COLLATE=C nm ft_nm > b; diff a b
	1,2c1,2
	< 0000000000004dd8 ? _DYNAMIC
	< 0000000000004fe8 ? _GLOBAL_OFFSET_TABLE_
	---
	> 0000000000004dd8 d _DYNAMIC
	> 0000000000004fe8 d _GLOBAL_OFFSET_TABLE_
	6c6
	< 0000000000003128 ? __GNU_EH_FRAME_HDR
	---
	> 0000000000003128 r __GNU_EH_FRAME_HDR
	18,19c18,19
	< 0000000000002940 ? _fini
	< 0000000000001000 ? _init
	---
	> 0000000000002940 T _fini
	> 0000000000001000 T _init
	24c24
	< 0000000000005058 D data_start
	---
	> 0000000000005058 W data_start
	*/
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

