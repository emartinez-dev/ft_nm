# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 15:15:27 by franmart          #+#    #+#              #
#    Updated: 2024/10/24 22:46:27 by franmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC_DIR = src/
SRCS =	elf_parser.c\
		file_utils.c\
		elf64_handler.c\
		elf32_handler.c\
		output_helpers.c\
		main.c

SRC = ${addprefix ${SRC_DIR}, ${SRCS}}
OBJ = ${SRC:.c=.o}

LIBFT = libs/libft/libft.a
LIBFT_DIR = libs/libft

INCLUDES = -I ./include -I ${LIBFT_DIR}/include

${NAME}: ${OBJ}
	@echo "Compiling $(NAME)..."
	@echo "Compiling dependencies..."
	@$(MAKE) -s all bonus -C $(LIBFT_DIR)
	@$(CC) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(NAME) compiled!"

%.o: %.c
	@git submodule update --init --recursive
	@${CC} ${FLAGS} $(INCLUDES) -c $^ -o $@

all: ${NAME} ${LIBFT}

clean:
	@echo "Removing files..."
	@echo "Removing dependencies..."
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@${RM} ${OBJ} ${BONUS_OBJ}

fclean: clean
	@${RM} ${NAME}
	@${RM} ${BONUS_NAME}
	@$(MAKE) -s fclean -C  $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re
