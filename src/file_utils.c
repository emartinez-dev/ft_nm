/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:31:05 by franmart          #+#    #+#             */
/*   Updated: 2024/10/24 22:16:39 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	open_file(char *file)
{
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("ft_nm: '", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
		perror(strerror(errno));
	}
	return (fd);
}

off_t	get_filesize(int fd)
{
	struct stat	st;

	if (fd == -1)
		return (-1);
	if (fstat(fd, &st) == -1)
	{
		perror(strerror(errno));
		close(fd);
		return (-1);
	}
	return (st.st_size);
}