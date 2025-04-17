# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 14:34:40 by andcarva          #+#    #+#              #
#    Updated: 2025/04/17 15:28:54 by andcarva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=cc
CFLAGS=-Wall -Wextra -Werror -g
OBJ_DIR = Obj_Libft

SRC= $(addprefix ./Src_lib/, ft_atoi.c ft_bzero.c ft_calloc.c \
		ft_isalnum.c ft_isascii.c ft_isalpha.c \
		ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_free_split.c)
		
SRC_LIST= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c 
			
PRINTF_SRC=	$(addprefix ./Printf_lib/, ft_ptf_util_func.c ft_ptf_hexfunc.c \
			ft_ptf_decfunc.c ft_printf.c )

GET_NEXT_LINE_SRC= $(addprefix ./Get_next_line_lib/, get_next_line.c \
		get_next_line_utils.c)

OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
OBJ_LIST= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_LIST:.c=.o)))
PRINTF_OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(PRINTF_SRC:.c=.o)))
GET_NEXT_LINE_OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(GET_NEXT_LINE_SRC:.c=.o)))

all: $(NAME)
 
$(NAME): $(OBJ) $(OBJ_LIST) $(PRINTF_OBJ) $(GET_NEXT_LINE_OBJ)
	# echo "Creating library $(NAME)"
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: ./Src_lib/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: ./Printf_lib/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: ./Get_next_line_lib/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus: $(OBJ_LIST) $(NAME)
	@ar rcs $(NAME) $(OBJ_LIST)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all