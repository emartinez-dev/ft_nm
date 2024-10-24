/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:27:44 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 21:43:47 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_elf64(void *map)
{
	t_ELF64_header 			*header = map;
	t_ELF64_section_header	*sh = map + header->e_shoff;
	t_ELF64_section_header	*sh_sym = NULL;
	t_ELF64_section_header	*sh_str = NULL;

	uint64_t	i = -1;
	while (++i < header->e_shnum)
	{
		if (sh[i].sh_type == SHT_SYMTAB)
			sh_sym = &sh[i];
		if (sh[i].sh_type == SHT_STRTAB && i != header->e_shstrndx)
			sh_str = &sh[i];
	}
	if (sh_sym && sh_str)
	{
		t_ELF64_symbol	*symtab = map + sh_sym->sh_offset;
		uint64_t 		n_sym = sh_sym->sh_size / sh_sym->sh_entsize;
		uint16_t		n_sh = header->e_shnum;
		char			*strtab = map + sh_str->sh_offset;

		read_symbols_elf64(symtab, n_sym, n_sh, sh, strtab);
	}
	else if (!sh_sym)
		ft_putstr_fd("ft_nm: symbol table not found\n", STDERR_FILENO);
	else if (!sh_str)
		ft_putstr_fd("ft_nm: string table not found\n", STDERR_FILENO);
}

void	read_symbols_elf64(t_ELF64_symbol *symtab, uint64_t n_sym, uint16_t n_sh,
							t_ELF64_section_header *sh, char *strtab)
{
	uint64_t		i = -1;
	t_ELF64_symbol	**symbols;

	symbols = ft_calloc(n_sym, sizeof(t_ELF64_symbol *));
	while (++i < n_sym)
		symbols[i] = &symtab[i];
	symbols = sort_elf64_list(symbols, n_sym, strtab);
	i = -1;
	while (++i < n_sym)
		print_elf64_symbol(symbols[i], n_sh, sh, strtab);
}

void	print_elf64_symbol(t_ELF64_symbol *sym, uint16_t n_sh, t_ELF64_section_header *sh,
							char *strtab)
{
	char	class;

	if (!sym->st_name || sym->st_shndx >= n_sh)
		return ;
	if (sh[sym->st_shndx].sh_type == SHN_UNDEF)
		ft_printf("                 ");
	else
		print_number_with_padding(sym->st_value, 16);
	class = get_symbol_class_elf64(sym, sh);
	ft_printf("%c ", class);
	ft_printf("%s\n", &strtab[sym->st_name]);
}

char    get_symbol_class_elf64(t_ELF64_symbol *sym, t_ELF64_section_header *sh)
{
	t_ELF64_section_header	*sh_sym = &sh[sym->st_shndx];
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

t_ELF64_symbol **msort_elf64(t_ELF64_symbol **left, uint64_t len_l, t_ELF64_symbol **right,
							uint64_t len_r, char *str_table)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	k = 0;
	t_ELF64_symbol **temp = ft_calloc(sizeof(t_ELF64_symbol **), len_l + len_r);

	while (i < len_l && j < len_r)
	{

		char *s1 = &str_table[left[j]->st_name];
		char *s2 = &str_table[right[j]->st_name];
		if (ft_strncmpi(s1, s2, ft_strlen(s1)) <= 0)
			temp[k++] = left[i++];
		else
			temp[k++] = right[j++];
	}
	while (i < len_l)
		temp[k++] = left[i++];
	while (j < len_r)
		temp[k++] = right[j++];
	i = -1;
	while (++i < k)
		left[i] = temp[i];
	free(temp);
	return (left);
}

t_ELF64_symbol **sort_elf64_list(t_ELF64_symbol **list, uint64_t len, char *str_table)
{
	uint64_t	mid = len / 2;
	if (len <= 1)
		return (list);
	t_ELF64_symbol **left = sort_elf64_list(list, mid, str_table);
	t_ELF64_symbol **right = sort_elf64_list(list + mid, len - mid, str_table);
	return (msort_elf64(left, mid, right, len - mid, str_table));
}
