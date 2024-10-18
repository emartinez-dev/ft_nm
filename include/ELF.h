/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ELF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:05:40 by franmart          #+#    #+#             */
/*   Updated: 2024/10/18 17:45:34 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
# define ELF_H

# define EI_MAG0       0
# define EI_MAG1       1
# define EI_MAG2       2
# define EI_MAG3       3
# define EI_CLASS      4
# define EI_DATA       5
# define EI_VERSION    6
# define EI_OSABI      7
# define EI_ABIVERSION 8
# define EI_PAD        9
# define EI_NIDENT     16

# define ELFMAG0  0x7f
# define ELFMAG1  'E'
# define ELFMAG2  'L'
# define ELFMAG3  'F'

# define ELFCLASSNONE  0
# define ELFCLASS32    1
# define ELFCLASS64    2

# define ELFDATANONE  0
# define ELFDATA2LSB  1
# define ELFDATA2MSB  2

# define EV_NONE    0
# define EV_CURRENT 1

# define SHT_SYMTAB 0x2
# define SHT_STRTAB 0x3
# define SHT_NOBITS 0x8

# define SHF_WRITE		0x1
# define SHF_ALLOC		0x2
# define SHF_EXECINSTR	0x4

# define ST_TYPE(info) ((info) & 0xf)
# define ST_BIND(info) ((info) >> 4)
# define ST_VISIBILITY(other) ((other)&0x3)

# define STT_NOTYPE  0
# define STT_OBJECT  1
# define STT_FUNC    2
# define STT_SECTION 3
# define STT_FILE    4
# define STT_COMMON  5
# define STT_TLS     6

# define STB_LOCAL   0
# define STB_GLOBAL  1
# define STB_WEAK    2
# define STB_NUM     3
# define STB_LOOS    10
# define STB_HIOS    12
# define STB_LOPROC  13
# define STB_HIPROC  15

# define STV_DEFAULT	0
# define STV_INTERNAL	1
# define STV_HIDDEN		2
# define STV_PROTECTED	3

# define SHN_UNDEF	0
# define SHN_ABS	0xfff1
# define SHN_COMMON	0xfff2

#endif