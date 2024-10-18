/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:28 by franmart          #+#    #+#             */
/*   Updated: 2024/10/18 18:46:27 by franmart         ###   ########.fr       */
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

char    get_type_elf64(t_ELF64_symbol *sym, t_ELF64_section_header *section_h)
{
	char c = '?';
	(void) sym;
	(void) section_h;

	return (c);
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

