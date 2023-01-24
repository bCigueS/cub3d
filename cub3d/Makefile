# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 10:57:00 by sbeylot           #+#    #+#              #
#    Updated: 2023/01/24 11:09:12 by sbeylot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3d
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -g3

RM		:=	rm -rf

SRCS_DIR	:=	srcs/
SRCS_NAME	:=	main.c\
				raycasting/clean.c\
				raycasting/init_mlx.c\
				raycasting/drawing.c\
				raycasting/draw_line.c\
				raycasting/ray.c\
				raycasting/ray_intersection.c\
				raycasting/raycasting.c\
				raycasting/player.c\
				raycasting/event.c\
				raycasting/utils.c\
				parsing/utils_parsing.c\
				parsing/file_handler.c\
				parsing/parsing.c\
				parsing/parsing_map.c\
				parsing/textures_handler.c\
				parsing/colors_handler.c

SRCS		:=	$(wildcard $(SRCS_DIR)*.c)\

OBJS_DIR	:=	objs/
OBJS_NAME	:=	$(patsubst %.c, %.o, $(SRCS_NAME))
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJS_NAME))

DEPS		:=	$(addprefix	$(OBJS_DIR), $(SRCS_NAME:%.c=%.d))

HEADER_DIR	:=	/includes/
HEADER_NAME	:=	cub3d.h\
				clean.h\
				init_mlx.h\
				drawing.h\
				player.h\
				ray.h\
				event.h\
				parsing.h
HEADER		:=	-I.$(HEADER_DIR)

INCLUDE_LFT	:=	-L./libft -lft
INCLUDE_MLX	:=	-L./mlx	-lmlx -lXext -lX11 -lm


all: $(NAME)

$(NAME):	$(OBJS)
	make -C ./libft
	make -C ./mlx
	$(CC) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME) $(INCLUDE_LFT) $(INCLUDE_MLX)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)raycasting
	mkdir -p $(OBJS_DIR)parsing
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@ 

clean:
	make clean -C ./libft 
	make clean -C ./mlx
	$(RM) $(OBJS_DIR)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.SECONDARY: $(OBJS)

.PHONY: all clean fclean

