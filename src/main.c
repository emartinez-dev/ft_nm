/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:35:59 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 15:14:57 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int argc, char **argv)
{
	t_args	args = {0};
	t_list	*files = NULL;
	t_list	*new_file;

	(void) argc;
	int i = 0;
	while (argv[++i])
	{
		new_file = parse_args(argv[i], &args);
		if (new_file)
			ft_lstadd_front(&files, new_file);
	}
	if (!files)
		files = ft_lstnew(ft_strdup("a.out"));
	ft_lstclear(&files, free);
	return (0);
}