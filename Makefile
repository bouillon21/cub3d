# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 14:50:25 by cshelli           #+#    #+#              #
#    Updated: 2021/01/27 21:27:56 by cshelli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADER	= includes/

CC		= @gcc

SRCS	= main.c parser.c draw.c

OBJS	= $(SRCS:.c=.o)

LIBFT	= libft/libft.a

all: $(NAME) $(LIBFT)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

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

cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")