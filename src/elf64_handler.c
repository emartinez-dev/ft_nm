/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:27:44 by franmart          #+#    #+#             */
/*   Updated: 2024/10/22 00:01:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_elf64(void *map)
{
	t_ELF64_header 			*header = map;
	t_ELF64_section_header	*section_h = map + header->e_shoff;
	t_ELF64_section_header	*symbols_h = NULL;
	t_ELF64_section_header	*strings_h = NULL;
	t_ELF64_section_header	*shstrtab_h = NULL;

	uint64_t	i = 0;
	while (i < header->e_shnum)
	{
		if (section_h[i].sh_type == SHT_SYMTAB)
			symbols_h = &section_h[i];
		if (section_h[i].sh_type == SHT_STRTAB && i != header->e_shstrndx)
			strings_h = &section_h[i];
		if (i == header->e_shstrndx)
			shstrtab_h = &section_h[i];
		i++;
	}
	if (symbols_h && strings_h)
		read_symbols_elf64(map + symbols_h->sh_offset,
					symbols_h->sh_size / symbols_h->sh_entsize,
					map + strings_h->sh_offset, section_h,
					map + shstrtab_h->sh_offset, header->e_shnum);
	else if (!symbols_h)
		ft_putstr_fd("ft_nm: symbol table not found\n", STDERR_FILENO);
	else if (!strings_h)
		ft_putstr_fd("ft_nm: string table not found\n", STDERR_FILENO);
}

void	read_symbols_elf64(t_ELF64_symbol *symbol_table, uint64_t n_symbols,
							char *str_table, t_ELF64_section_header *section_h,
							char *shstrtab, uint16_t max_size)
{
	uint64_t		i = -1;
	t_ELF64_symbol	**symbols;

	symbols = ft_calloc(n_symbols, sizeof(t_ELF64_symbol *));
	while (++i < n_symbols)
		symbols[i] = &symbol_table[i];
	symbols = sort_elf64_list(symbols, n_symbols, str_table);
	i = -1;
	while (++i < n_symbols)
		print_elf64_symbol(symbols[i], str_table, section_h, shstrtab, max_size);
}

void	print_elf64_symbol(t_ELF64_symbol *sym, char *str_table,
							t_ELF64_section_header *section_h, char *shstrtab, uint16_t max_size)
{
	char		type = '?';

	if (!sym->st_name || ST_TYPE(sym->st_info) > STT_FUNC || sym->st_shndx > max_size)
		return ;
	if (section_h[sym->st_shndx].sh_type != SHN_UNDEF)
		print_number_with_padding(sym->st_value, 16);
	else
		ft_printf("                 ");
	type = get_type_elf64(sym, section_h, shstrtab);
	ft_printf("%c ", type);
	ft_printf("%s\n", &str_table[sym->st_name]);
}

void	swap_elf64(t_ELF64_symbol **a, t_ELF64_symbol **b);

// Bubblesort because I am lazy and there are few symbols
t_ELF64_symbol	**sort_elf64_list(t_ELF64_symbol **list, uint64_t len,
							char *str_table)
{
	uint64_t i;
	uint64_t j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			char *s1 = &str_table[list[j]->st_name];
			char *s2 = &str_table[list[j + 1]->st_name];
			if (ft_strncmp(s1, s2, ft_strlen(s1)) > 0)
				swap_elf64(&list[j], &list[j + 1]);
			j++;
		}
		i++;
	}
	return (list);
}

void	swap_elf64(t_ELF64_symbol **a, t_ELF64_symbol **b)
{
	t_ELF64_symbol	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}