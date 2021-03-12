# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 14:50:25 by cshelli           #+#    #+#              #
#    Updated: 2021/03/12 11:26:52 by cshelli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER	= includes/

LIBFT	= libft/libft.a

CC		= @gcc

SRC_DIR	= src/

MLX_CR	= libmlx.a

SRC	= $(SRC_DIR)cub3d.c $(SRC_DIR)parser.c $(SRC_DIR)parser_util.c $(SRC_DIR)draw.c $(SRC_DIR)move.c $(SRC_DIR)valid_param.c $(SRC_DIR)valid_map.c $(SRC_DIR)cub_init.c $(SRC_DIR)dda_algorithm.c $(SRC_DIR)sprite.c $(SRC_DIR)sort.c $(SRC_DIR)screen.c


INCLUDE = -Imlx -Iincludes

OBJ		= $(patsubst src/%.c, obj/%.o, $(SRC))

OUT_DIR = obj

MKDIR_P	= mkdir -p

.PHONY: all re clean fclean

all: $(OUT_DIR) $(LIBFT) $(MLX_CR) $(NAME)

obj/%.o:	src/%.c
	@$(CC) -g -Wall -Wextra -Werror -Imlx -I $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJ) $(LIBFT) $(HEADER)
	@$(CC) $(OBJ) mlx/libmlx.a -I $(INCLUDE) $(LIBFT) -framework OpenGL -framework AppKit -o $(NAME)
	@echo '$(cgreen)Good compile!'

$(LIBFT):
	@make -C libft
	@echo '$(cgreen)Libft compile$(cwhite)'

$(MLX_CR):
	@make -C mlx

$(OUT_DIR):
	@$(MKDIR_P) $@
	@echo '$(cgreen)$@ dir create$(cwhite)'
	@echo "\033[1A"

re: fclean all

clean:
	@/bin/rm -rf $(OUT_DIR)
	@cd libft && make clean
	@echo '$(ccred)$(OUT_DIR) delete$(cwhite)'

fclean: clean
	@make fclean -C libft
	@make clean -C mlx
	@/bin/rm -f $(NAME)
	@echo '$(ccred)$(NAME) file delete$(cwhite)'
	
cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")