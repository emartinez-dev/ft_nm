/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf32_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:31:52 by franmart          #+#    #+#             */
/*   Updated: 2024/10/22 21:48:20 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_elf32(void *map)
{
	t_ELF32_header 			*header = map;
	t_ELF32_section_header	*sh = map + header->e_shoff;
	t_ELF32_section_header	*sh_sym = NULL;
	t_ELF32_section_header	*sh_str = NULL;

	uint32_t	i = -1;
	while (++i < header->e_shnum)
	{
		if (sh[i].sh_type == SHT_SYMTAB)
			sh_sym = &sh[i];
		if (sh[i].sh_type == SHT_STRTAB && i != header->e_shstrndx)
			sh_str = &sh[i];
	}
	if (sh_sym && sh_str)
	{
		t_ELF32_symbol	*symtab = map + sh_sym->sh_offset;
		uint32_t 		n_sym = sh_sym->sh_size / sh_sym->sh_entsize;
		uint16_t		n_sh = header->e_shnum;
		char			*strtab = map + sh_str->sh_offset;

		read_symbols_elf32(symtab, n_sym, n_sh, sh, strtab);
	}
	else if (!sh_sym)
		ft_putstr_fd("ft_nm: symbol table not found\n", STDERR_FILENO);
	else if (!sh_str)
		ft_putstr_fd("ft_nm: string table not found\n", STDERR_FILENO);
}

void	read_symbols_elf32(t_ELF32_symbol *symtab, uint32_t n_sym, uint16_t n_sh,
							t_ELF32_section_header *sh, char *strtab)
{
	uint32_t		i = -1;
	t_ELF32_symbol	**symbols;

	symbols = ft_calloc(n_sym, sizeof(t_ELF32_symbol *));
	while (++i < n_sym)
		symbols[i] = &symtab[i];
	symbols = sort_elf32_list(symbols, n_sym, strtab);
	i = -1;
	while (++i < n_sym)
		print_elf32_symbol(symbols[i], n_sh, sh, strtab);
}

void	print_elf32_symbol(t_ELF32_symbol *sym, uint16_t n_sh, t_ELF32_section_header *sh,
							char *strtab)
{
	char	class;

	if (!sym->st_name || sym->st_shndx >= n_sh)
		return ;
	if (sh[sym->st_shndx].sh_type == SHN_UNDEF)
		ft_printf("         ");
	else
		print_number_with_padding(sym->st_value, 8);
	class = get_symbol_class_elf32(sym, sh);
	ft_printf("%c ", class);
	ft_printf("%s\n", &strtab[sym->st_name]);
}

char    get_symbol_class_elf32(t_ELF32_symbol *sym, t_ELF32_section_header *sh)
{
	t_ELF32_section_header	*sh_sym = &sh[sym->st_shndx];
	char					class = '?';
	unsigned char			type = ST_TYPE(sym->st_info);
	unsigned char			bind = ST_BIND(sym->st_info);
	unsigned char			visibility = ST_VISIBILITY(sym->st_other);

	switch (sym->st_shndx)
	{
		case SHN_UNDEF:
			if (bind == STB_WEAK)
				return (type == STT_OBJECT) ? 'v' : 'w';
			return 'U';
		case SHN_ABS:
			return 'A';
		case SHN_COMMON:
			return 'C';
	}
	if (type == STT_FUNC || sh_sym->sh_flags & SHF_EXECINSTR)
		class = 'T';
	else if (sh_sym->sh_type == SHT_NOBITS && (sh_sym->sh_flags & (SHF_ALLOC | SHF_WRITE)))
		class = 'B';
	else if (sh_sym->sh_flags & SHF_ALLOC && !(sh_sym->sh_flags & SHF_WRITE))
		class = 'R';
	else if (sh_sym->sh_flags & (SHF_ALLOC | SHF_WRITE))
		class = 'D';

	if (bind == STB_WEAK)
        return (visibility == STV_HIDDEN) ? 'v' : 'W';

	if (bind == STB_LOCAL && class != '?')
        class = ft_tolower(class);
	return (class);
}

void	swap_elf32(t_ELF32_symbol **a, t_ELF32_symbol **b)
{
	t_ELF32_symbol	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Bubblesort because I am lazy and there are few symbols
t_ELF32_symbol	**sort_elf32_list(t_ELF32_symbol **list, uint32_t len, char *str_table)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			char *s1 = &str_table[list[j]->st_name];
			char *s2 = &str_table[list[j + 1]->st_name];
			if (ft_strncmp(s1, s2, ft_strlen(s1)) > 0)
				swap_elf32(&list[j], &list[j + 1]);
			j++;
		}
		i++;
	}
	return (list);
}
