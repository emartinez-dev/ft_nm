/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:31:17 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 15:09:14 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void error_invalid_arg(char arg);

t_list    *parse_args(char *arg, t_args *args)
{
	if (arg[0] != '-')
		return ft_lstnew(ft_strdup(arg));
	int i = 0;
	while (arg[++i])
	{
		switch (arg[i])
		{
		case 'a':
			args->a_display_debug = true;
			break;
		case 'g':
			args->g_only_external = true;
			break;
		case 'u':
			args->u_only_undefined = true;
			break;
		case 'r':
			args->r_reverse = true;
			break;
		case 'p':
			args->p_dont_sort = true;
			break;
		default:
			error_invalid_arg(arg[i]);
			break;
		}
	}
	return NULL;
}

static void error_invalid_arg(char arg)
{
	ft_putstr_fd("ft_nm: invalid option -- '", STDERR_FILENO);
	ft_putchar_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	exit(1);
}