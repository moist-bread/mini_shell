# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 15:43:01 by andcarva          #+#    #+#              #
#    Updated: 2025/04/07 18:29:17 by andcarva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -->┊( NAMES )
NAME	=	minishell
LIBFT	=	./Inc/Libft/libft.a


# -->┊( COMMANDS AND FLAGS )
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g

# -->┊( DIRECTORIES )
SRC_DIR			=	Src
OBJS_DIR		=	Objs
MINISHELL_DIR	=	Minishell
EXEC_DIR		= 	Exec
PARSE_DIR		=	Parse

# -->┊( SOURCES AND OBJS )
MAIN_C			=	minishell_main.c
EXEC_MAIN_C		=	exec_main.c
PARSE_MAIN_C	=	parse_main.c

MAIN		=	$(addprefix	$(MINISHELL_DIR)/, $(MAIN_C))
EXEC_MAIN	=	$(addprefix	$(EXEC_DIR)/, $(EXEC_MAIN_C))
PARSE_MAIN	=	$(addprefix	$(PARSE_DIR)/, $(PARSE_MAIN_C))

SRC_MINISHELL_FILES	=	$(addprefix	$(MINISHELL_DIR)/, )
SRC_EXEC_FILES		=	$(addprefix	$(EXEC_DIR)/, )
SRC_PARSE_FILES		=	$(addprefix	$(PARSE_DIR)/, )

SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_EXEC_FILES) $(SRC_PARSE_FILES) $(SRC_MINISHELL_FILES))
SRC_MAIN		=	$(addprefix $(SRC_DIR)/, $(MAIN))
SRC_MAIN_EXEC	=	$(addprefix $(SRC_DIR)/, $(EXEC_MAIN))
SRC_MAIN_PARSE	=	$(addprefix $(SRC_DIR)/, $(PARSE_MAIN))

OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))
OBJS_MAIN		=	$(addprefix $(OBJS_DIR)/, $(MAIN_C:.c=.o))
OBJS_MAIN_EXEC	=	$(addprefix $(OBJS_DIR)/, $(EXEC_MAIN_C:.c=.o))
OBJS_MAIN_PARSE	=	$(addprefix $(OBJS_DIR)/, $(PARSE_MAIN_C:.c=.o))

# -->┊( RULES )
all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS) $(LIBFT)
	$(M_COMP)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS) $(LIBFT) -o $(NAME)
	$(M_DONE)

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(MINISHELL_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(EXEC_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(PARSE_DIR)/%.c | $(OBJS_DIR)
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
