/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:28 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 19:42:36 by franmart         ###   ########.fr       */
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

void    print_type(unsigned char type, unsigned char bind)
{
	char c = '?';

    if (bind == STB_LOCAL)
	{
		if (type == STT_OBJECT) c = 'd';
		if (type == STT_FUNC) c = 't';
		if (type == STT_SECTION) c = 's';
		if (type == STT_COMMON) c = 'c';
	}
    else if (bind == STB_GLOBAL)
	{
		if (type == STT_OBJECT) c = 'D';
		if (type == STT_FUNC) c = 'T';
		if (type == STT_SECTION) c = 'S';
		if (type == STT_COMMON) c = 'B';
		if (type == STT_NOTYPE) c = 'N';
	}
    else if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT) c = 'w';
		if (type == STT_FUNC) c = 'w';
		if (type == STT_NOTYPE) c = 'W';
	}
	ft_printf("%c ", c);
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

