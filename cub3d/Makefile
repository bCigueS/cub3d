# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 10:57:00 by sbeylot           #+#    #+#              #
#    Updated: 2023/01/27 13:42:59 by fbily            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	cub3D
NAME_BONUS := cub3D_bonus
CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra -MMD -MP -g3

RM		:=	rm -rf

SRCS_DIR	:=	srcs/
SRCS_NAME	:=	main.c\
				raycasting/cub3d.c\
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
				raycasting/utils2.c\
				raycasting/door.c\
				raycasting/door_texture.c\
				parsing/utils_parsing.c\
				parsing/file_handler.c\
				parsing/parsing.c\
				parsing/parsing_map.c\
				parsing/textures_handler.c\
				parsing/colors_handler.c\
				parsing/parsing_map_utils.c

SRCS_DIR_B	:=	srcs_bonus/
SRCS_NAME_B	:=	main_bonus.c\
				raycasting/cub3d_bonus.c\
				raycasting/clean_bonus.c\
				raycasting/init_mlx_bonus.c\
				raycasting/drawing_bonus.c\
				raycasting/draw_line_bonus.c\
				raycasting/ray_bonus.c\
				raycasting/ray_intersection_bonus.c\
				raycasting/raycasting_bonus.c\
				raycasting/player_bonus.c\
				raycasting/event_bonus.c\
				raycasting/utils_bonus.c\
				raycasting/utils2_bonus.c\
				raycasting/door_bonus.c\
				raycasting/door_texture_bonus.c\
				parsing/utils_parsing_bonus.c\
				parsing/file_handler_bonus.c\
				parsing/parsing_bonus.c\
				parsing/parsing_map_bonus.c\
				parsing/textures_handler_bonus.c\
				parsing/colors_handler_bonus.c\
				parsing/parsing_map_utils_bonus.c
SRCS_B		:=	$(wildcard $(SRCS_DIR_B)*.c)
OBJS_DIR_B	:=	objs_bonus/
OBJS_NAME_B	:=	$(patsubst %.c, %.o, $(SRCS_NAME_B))
OBJS_B		:=	$(addprefix $(OBJS_DIR_B), $(OBJS_NAME_B))
DEPS_B		:=	$(addprefix	$(OBJS_DIR_B), $(SRCS_NAME_B:%.c=%.d))

SRCS		:=	$(wildcard $(SRCS_DIR)*.c)
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
				parsing.h\
				door.h
HEADER		:=	-I.$(HEADER_DIR)

INCLUDE_LFT	:=	-L./libft -lft
INCLUDE_MLX	:=	-L./mlx	-lmlx -lXext -lX11 -lm

############ COLORS ############

GREEN = "\033[92m"
CYAN = "\033[96m"
BOLD = "\033[1m"
NC = "\033[0m"
# NC = No Colors (use for reset)


all: $(NAME)

$(NAME):	$(OBJS)
	make --no-print-directory title 
	@make --no-print-directory -C ./libft
	@make --no-print-directory -C ./mlx
	@$(CC) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME) $(INCLUDE_LFT) $(INCLUDE_MLX)
	@echo ${CYAN}${BOLD}Compilation ${NC}[${GREEN}OK${NC}]

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_B)
	make --no-print-directory title
	@make --no-print-directory -C ./libft
	@make --no-print-directory -C ./mlx
	@$(CC) $(CFLAGS) $(HEADER) $(OBJS_B) -o $(NAME_BONUS) $(INCLUDE_LFT) $(INCLUDE_MLX)
	@echo ${CYAN}${BOLD}Compilation Bonus ${NC}[${GREEN}OK${NC}]

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)raycasting
	@mkdir -p $(OBJS_DIR)parsing
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@ 

#BONUS
$(OBJS_DIR_B)%.o: $(SRCS_DIR_B)%.c
	@mkdir -p $(OBJS_DIR_B)
	@mkdir -p $(OBJS_DIR_B)raycasting
	@mkdir -p $(OBJS_DIR_B)parsing
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@ 


clean:
	@make $@ --no-print-directory -C ./libft 
	@make $@ --no-print-directory -C ./mlx
	@$(RM) $(OBJS_DIR)
	@$(RM) $(OBJS_DIR_B)
	@echo ${CYAN}${BOLD}Objects cleaned${NC}

fclean: clean
	@make $@ --no-print-directory -C ./libft
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@echo ${CYAN}${BOLD}Cleanning ${NC}[${GREEN}OK${NC}]

re: fclean all

-include $(DEPS)

.SECONDARY: $(OBJS) $(OBJS_B)

.PHONY: all clean fclean re

#ASCII = ANSI Shadow
define TITLE 
\033[92m

 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 
                                         
\033[0m                                                                                                           
endef
export TITLE

title :
	clear
	@echo "$$TITLE"

-include ${DEPS}

