/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:35:59 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 18:51:48 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int argc, char **argv)
{
	t_list	*files = NULL;
	t_list	*new_file;

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
	parse_elfs_list(files);
	ft_printf_flush_buffer();
	ft_lstclear(&files, free);
	return (0);
}