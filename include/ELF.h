/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ELF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:05:40 by franmart          #+#    #+#             */
/*   Updated: 2024/10/12 16:10:00 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
# define ELF_H

# include "ft_nm.h"

#define EI_MAG0       0
#define EI_MAG1       1
#define EI_MAG2       2
#define EI_MAG3       3
#define EI_CLASS      4
#define EI_DATA       5
#define EI_VERSION    6
#define EI_OSABI      7
#define EI_ABIVERSION 8
#define EI_PAD        9
#define EI_NIDENT     16

#define ELFMAG0  0x7f
#define ELFMAG1  'E'
#define ELFMAG2  'L'
#define ELFMAG3  'F'

#define ELFCLASSNONE  0
#define ELFCLASS32    1
#define ELFCLASS64    2

#define ELFDATANONE  0
#define ELFDATA2LSB  1
#define ELFDATA2MSB  2

#define EV_NONE    0
#define EV_CURRENT 1

#endif