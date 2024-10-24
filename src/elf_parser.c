/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:27:13 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 22:45:50 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ELF.h"

int	parse_elf(char *filename)
{
	void	*map;
	int		fd;
	off_t	size;

	fd = open_file(filename);
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
	int elf_class = get_elf_class(map, filename);
	if (elf_class == ELFCLASS64)
		process_elf64(map);
	else if (elf_class == ELFCLASS32)
		process_elf32(map);
	else
		ft_putstr_fd("ft_nm: ELF class not recognized\n", STDERR_FILENO);
	if (munmap(map, size) == -1)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	close(fd);
	return (0);
}

int	parse_elf_list(t_list *files)
{
	char	*filename;
	int		status = 0;

	while (files)
	{
		filename = files->content;
		if (parse_elf(filename))
			status = 1;
		files = files->next;
	}
	return (status);
}

int	get_elf_class(void *map, char *file)
{
	unsigned char	*e_ident = map;

	if (!(e_ident[EI_MAG0] == ELFMAG0 && e_ident[EI_MAG1] == ELFMAG1 &&
	e_ident[EI_MAG2] == ELFMAG2 && e_ident[EI_MAG3] == ELFMAG3))
	{
		ft_putstr_fd("ft_nm: '", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("': file format not recognized\n", STDERR_FILENO);
		return (-1);
	}
	if (e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_putstr_fd("ft_nm: '", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("': unknown ELF class\n", STDERR_FILENO);
		return (-1);
	}
	return (e_ident[EI_CLASS]);
}