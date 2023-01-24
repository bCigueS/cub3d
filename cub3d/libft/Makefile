# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 15:31:55 by fbily             #+#    #+#              #
#    Updated: 2023/01/19 15:16:16 by fbily            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_PATH = ./srcs/
SRC = ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_printf.c \
		ft_print_hexa.c \
		ft_print_int.c \
		ft_print_ptr.c \
		ft_print_string.c \
		ft_printf_fd.c \
		ft_print_hexa_fd.c \
		ft_print_int_fd.c \
		ft_print_ptr_fd.c \
		ft_print_string_fd.c \

SRCS = $(addprefix ${SRC_PATH}, ${SRC})

OBJ_PATH	= obj/
OBJ = ${SRC:.c=.o}

OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I./includes/

DEPS = $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -rf

####### COLORS #######

GREEN = "\033[92m"
CYAN = "\033[96m"
BOLD = "\033[1m"
NC = "\033[0m"
# NC = No Colors (use for reset)

all : ${NAME}

${NAME} : ${OBJS}
	@ar rc ${NAME} $^
	@echo ${CYAN}${BOLD}Libft ${NC}[${GREEN}OK${NC}]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p ${OBJ_PATH}
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

clean :
	@${RM} ${OBJ_PATH}

fclean : clean
	@${RM} ${NAME}

re : fclean all

-include ${DEPS}

.PHONY: all clean fclean re
