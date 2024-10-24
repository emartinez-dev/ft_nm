/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:35:59 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 22:24:34 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int argc, char **argv)
{
	t_list	*files = NULL;
	t_list	*new_file;
	int		status;

	(void) argc;
	int i = 0;
	while (argv[++i])
	{
		new_file = parse_args(argv[i]);
		if (new_file)
			ft_lstadd_front(&files, new_file);
	}
	if (!files)
		files = ft_lstnew(ft_strdup("a.out"));
	status = parse_elf_list(files);
	ft_printf_flush_buffer();
	ft_lstclear(&files, free);
	return (status);
}

t_list    *parse_args(char *arg)
{
	if (arg[0] != '-')
		return ft_lstnew(ft_strdup(arg));
	ft_putstr_fd("ft_nm: invalid option -- '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	exit(1);
}
