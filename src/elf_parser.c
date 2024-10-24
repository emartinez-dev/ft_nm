/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:27:13 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 21:51:43 by franmart         ###   ########.fr       */
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
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		close(fd);
		return (1);
	}
	int elf_type = get_elf_type(map, file);
	if (elf_type == ELFCLASS64)
		handle_elf64(map);
	else if (elf_type == ELFCLASS32)
		handle_elf32(map);
	if (munmap(map, size) == -1)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	close(fd);
	return (0);
}

int	get_elf_type(void *map, char *file)
{
	unsigned char	*e_ident = map;

	if (!(e_ident[EI_MAG0] == ELFMAG0 && e_ident[EI_MAG1] == ELFMAG1 &&
	e_ident[EI_MAG2] == ELFMAG2 && e_ident[EI_MAG3] == ELFMAG3))
	{
		ft_putstr_fd("ft_nm: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": file format not recognized\n", STDERR_FILENO);
		return (-1);
	}
	if (e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_putstr_fd("ft_nm: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": unknown ELF class\n", STDERR_FILENO);
		return (-1);
	}
	return (e_ident[EI_CLASS]);
}