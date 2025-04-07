# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 15:43:01 by andcarva          #+#    #+#              #
#    Updated: 2025/04/07 11:44:09 by rduro-pe         ###   ########.fr        #
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
EXEC_MAIN	=	exec_main.c
PARSE_MAIN	=	parse_main.c

SRC_EXEC_FILES	=	


SRC_PARSE_FILES	=	


SRC_DIR			=	Src
SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_EXEC_FILES) $(SRC_PARSE_FILES))
SRC_MAIN		=	$(addprefix $(SRC_DIR)/, $(MAIN))
SRC_MAIN_EXEC	=	$(addprefix $(SRC_DIR)/, $(EXEC_MAIN))
SRC_MAIN_PARSE	=	$(addprefix $(SRC_DIR)/, $(PARSE_MAIN))

OBJS_DIR		=	Objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))
OBJS_MAIN		=	$(addprefix $(OBJS_DIR)/, $(MAIN:.c=.o))
OBJS_MAIN_EXEC	=	$(addprefix $(OBJS_DIR)/, $(EXEC_MAIN:.c=.o))
OBJS_MAIN_PARSE	=	$(addprefix $(OBJS_DIR)/, $(PARSE_MAIN:.c=.o))

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

exec: $(OBJS_MAIN_EXEC) $(OBJS) $(LIBFT)
	$(M_COMP_E)
	@$(CC) $(CFLAGS) $(OBJS_MAIN_EXEC) $(OBJS) $(LIBFT) -o $(NAME)
	$(M_DONE)

parse: $(OBJS_MAIN_PARSE) $(OBJS) $(LIBFT)
	$(M_COMP_P)
	@$(CC) $(CFLAGS) $(OBJS_MAIN_PARSE) $(OBJS) $(LIBFT) -o $(NAME)
	$(M_DONE)

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
M_COMP_E	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) EXE $(NAME) $(BLK)$(DEF)"
M_COMP_P	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) PAR $(NAME) $(BLK)$(DEF)"
M_REM		= @echo "$(BLK)-->┊$(BLU)  Removing:  $(DEF)$(BLK)$(WHTB) $(NAME) $(BLK)$(DEF)"
M_REMOBJS	= @echo "$(BLK)-->┊$(BLU)  Removing: $(BWHT) $(NAME)/objs $(BLK)$(DEF)"
M_DONE		= @echo "$(BLK)-->┊$(BGRN)  DONE!!$(DEF)"
