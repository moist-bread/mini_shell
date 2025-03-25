# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 15:43:01 by andcarva          #+#    #+#              #
#    Updated: 2025/03/25 17:29:59 by rduro-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -->┊( NAMES )
NAME	=	minishell
LIBFT	=	./Inc/Libft/libft.a


# -->┊( COMMANDS AND FLAGS )
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g


# -->┊( SOURCES AND OBJS )
MAIN		=	minishell_main.c
SRC_FILES	=	

SRC_DIR		=	Src
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_MAIN	=	$(addprefix $(SRC_DIR)/, $(MAIN))

OBJS_DIR	=	Objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))
OBJS_MAIN	=	$(addprefix $(OBJS_DIR)/, $(MAIN:.c=.o))


# -->┊( RULES )
all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS) $(LIBFT)
	$(M_COMP)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS) $(LIBFT) -o $(NAME)
	$(M_DONE)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@make -C ./Inc/Libft -s

clean:
	@make clean -C ./Inc/Libft -s
	$(M_REMOBJS)
	@rm -rf $(OBJS_DIR)
	$(M_DONE)

fclean: clean
	@rm -rf $(LIBFT)
	$(M_REM)
	@rm -rf $(NAME)
	$(M_DONE)
	
re: fclean all

.PHONY: all clean fclean re bonus exe


# -->┊( EXE TEST RULES )
exe: all
	./minishell


# -->┊( COSMETICS )

#->┊ normal colors
DEF	=	\e[0;39m
BLK	= 	\e[0;30m
BLU	=	\e[0;34m
GRN	=	\e[0;32m

#->┊ bold colors
BGRN	=	\e[1;32m
BWHT	=	\e[1;37m

#->┊ background colors
WHTB 	=	\e[47m

#->┊ messages
M_COMP		= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) $(NAME) $(BLK)$(DEF)"
M_REM		= @echo "$(BLK)-->┊$(BLU)  Removing:  $(DEF)$(BLK)$(WHTB) $(NAME) $(BLK)$(DEF)"
M_REMOBJS	= @echo "$(BLK)-->┊$(BLU)  Removing: $(BWHT) $(NAME)/objs $(BLK)$(DEF)"
M_DONE		= @echo "$(BLK)-->┊$(BGRN)  DONE!!$(DEF)"
