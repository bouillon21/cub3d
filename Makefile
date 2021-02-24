# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 14:50:25 by cshelli           #+#    #+#              #
#    Updated: 2021/02/23 19:50:37 by cshelli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER	= includes/

CC		= @gcc

SRC_DIR	= src/

SRCS	= $(SRC_DIR)cub3D.c $(SRC_DIR)parser.c $(SRC_DIR)parser_util.c $(SRC_DIR)draw.c $(SRC_DIR)move.c $(SRC_DIR)valid_param.c $(SRC_DIR)valid_map.c $(SRC_DIR)cub_init.c $(SRC_DIR)dda_algorithm.c

OBJS	= $(SRCS:.c=.o)

START	= ./cub3D

LIBFT	= libft/libft.a

all: $(NAME) $(LIBFT)
	@$(START)

.c.o:
				${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) $(LIBFT)
	$(CC) mlx/libmlx.a $(LIBFT) $(SRCS) -I $(HEADER) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	@cd libft && make
	@echo '$(cgreen)Libft compile$(cwhite)'

clean:
	@/bin/rm -rf *.o
	@cd libft && make fclean
	@echo '$(ccred)delete'

fclean: clean
	@/bin/rm -f $(NAME)
	@echo '$(ccred)$(NAME) file delete$(cwhite)'

re: fclean all

cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")