/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:27:13 by franmart          #+#    #+#             */
/*   Updated: 2024/10/21 23:31:05 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ELF.h"

int	parse_elfs_list(t_list *files)
{
	char	*file;
	int		status;

	status = 0;
	while (files)
	{
		file = files->content;
		if (parse_elf(file))
			status = 1;
		files = files->next;
	}
	return (status);
}

int	parse_elf(char *file)
{
	void	*map;
	int		fd;
	off_t	size;

	fd = open_file(file);
	size = get_filesize(fd);
	if (size == -1)
		return (1);

	map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
	{
		ft_printf("%s: ", strerror(errno));
		close(fd);
		return (1);
	}
	int elf_type = get_elf_type(map, file);
	if (elf_type == -1 || elf_type == ELFCLASSNONE)
		return (1);
	if (elf_type == ELFCLASS64)
		handle_elf64(map);
	return (0);
}

int	get_elf_type(void *map, char *file)
{
	unsigned char	*e_ident = map;

	if (!(e_ident[EI_MAG0] == ELFMAG0 && e_ident[EI_MAG1] == ELFMAG1 &&
	e_ident[EI_MAG2] == ELFMAG2 && e_ident[EI_MAG3] == ELFMAG3))
	{
		ft_printf("ft_nm: %s: file format not recognized\n", file);
		return (-1);
	}
	if (e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_printf("ft_nm: %s: unknown ELF class\n", file);
		return (-1);
	}
	return (e_ident[EI_CLASS]);
}