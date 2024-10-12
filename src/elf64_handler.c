/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:27:44 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 19:59:57 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_elf64(void *map)
{
	t_ELF64_header 			*header = map;
	t_ELF64_section_header	*section_h = map + header->e_shoff;
	t_ELF64_section_header	*symbols_h = NULL;
	t_ELF64_section_header	*strings_h = NULL;

	uint64_t	i = 0;
	while (i < header->e_shnum)
	{
		if (section_h[i].sh_type == SHT_SYMTAB)
			symbols_h = &section_h[i];
		if (section_h[i].sh_type == SHT_STRTAB && i != header->e_shstrndx)
			strings_h = &section_h[i];
		i++;
	}
	if (symbols_h && strings_h)
		print_elf64(map + symbols_h->sh_offset,
					symbols_h->sh_size / symbols_h->sh_entsize,
					map + strings_h->sh_offset);
	else
		ft_printf("Symbol table or string table not found\n");
}

void	print_elf64(t_ELF64_symbol *symbol_table, uint64_t n_symbols,
					char *str_table)
{
	uint64_t	i = 0;

	while (i < n_symbols)
	{
		t_ELF64_symbol *sym = &symbol_table[i];
		if (sym->st_value != 0)
			print_number_with_padding(sym->st_value, 16);
		else
			ft_printf("                 ");
		print_type(ELF64_ST_TYPE(sym->st_info),
				ELF64_ST_BIND(sym->st_info));
		ft_printf("%s\n", &str_table[sym->st_name]);
		i++;
	}
}