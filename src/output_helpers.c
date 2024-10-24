/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:06:28 by franmart          #+#    #+#             */
/*   Updated: 2024/10/22 19:56:11 by franmart         ###   ########.fr       */
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

