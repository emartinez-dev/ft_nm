/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:31:17 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 18:53:10 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_list    *parse_args(char *arg)
{
	if (arg[0] != '-')
		return ft_lstnew(ft_strdup(arg));
	ft_putstr_fd("ft_nm: invalid option -- '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	exit(1);
}