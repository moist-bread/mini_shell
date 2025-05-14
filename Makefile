
# -->┊( NAMES )
NAME	=	minishell
LIBFT	=	./Inc/Libft/libft.a


# -->┊( COMMANDS AND FLAGS )
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
RL		=	-lreadline
VAL		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
FDFLAGS	=	--track-fds=yes #--trace-children=yes
SUPP	=	--suppressions=readline.supp

# -->┊( DIRECTORIES )
SRC_DIR			=	Src
OBJS_DIR		=	Objs
MINISHELL_DIR	=	Minishell
EXEC_DIR		= 	Exec
PARSE_DIR		=	Parse

# -->┊( SOURCES AND OBJS )
MAIN_C			=	minishell_main.c

EXEC_MAIN_C		=	exec_main.c 
EXEC_FILES_C	=	struct_init.c distributer.c \
					pipe_process.c redir_handler.c pipe_child_pro.c \
					matrix_utils.c matrix_quick_sort.c \
					export.c export_utils.c env.c get_env.c unset.c echo.c exit.c directory.c \
					ft_strcmp.c ft_strndup.c ft_iswhitespace.c

PARSE_MAIN_C	=	parse_main.c
PARSE_FILES_C	= 	tokenization_utils.c tokenization.c checks.c space_utils.c \
					check_types_utils.c types.c errors.c cracked_split.c cracked_split_utils.c \
					tree.c tree_utils.c tree_func_utils.c expansions.c expansions_utils.c \
					expansions_len.c

MAIN		=	$(addprefix	$(MINISHELL_DIR)/, $(MAIN_C))
EXEC_MAIN	=	$(addprefix	$(EXEC_DIR)/, $(EXEC_MAIN_C))
PARSE_MAIN	=	$(addprefix	$(PARSE_DIR)/, $(PARSE_MAIN_C))

OBJS_PARSE		=	$(addprefix $(OBJS_DIR)/, $(PARSE_FILES_C:.c=.o))
OBJS_EXEC		=	$(addprefix $(OBJS_DIR)/, $(EXEC_FILES_C:.c=.o))
OBJS_MAIN		=	$(addprefix $(OBJS_DIR)/, $(MAIN_C:.c=.o))
OBJS_MAIN_EXEC	=	$(addprefix $(OBJS_DIR)/, $(EXEC_MAIN_C:.c=.o))
OBJS_MAIN_PARSE	=	$(addprefix $(OBJS_DIR)/, $(PARSE_MAIN_C:.c=.o))

# -->┊( RULES )
all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_PARSE) $(LIBFT)
	$(M_COMP)
	@$(CC) $(CFLAGS) $(RL) $(OBJS_MAIN) $(OBJS_PARSE) $(LIBFT) -o $(NAME)
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

exec: $(OBJS_MAIN_EXEC) $(OBJS_EXEC) $(OBJS_PARSE) $(LIBFT)
	$(M_COMP_E)
	@$(CC) $(CFLAGS) $(RL) $(OBJS_MAIN_EXEC) $(OBJS_EXEC) $(OBJS_PARSE) $(LIBFT) $(RL) -o $(NAME)
	$(M_DONE)

parse: $(OBJS_MAIN_PARSE) $(OBJS_PARSE) $(OBJS_EXEC) $(LIBFT)
	$(M_COMP_P)
	@$(CC) $(CFLAGS) $(OBJS_MAIN_PARSE) $(OBJS_EXEC) $(OBJS_PARSE) $(LIBFT) $(RL) -o $(NAME)
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

rp: fclean parse

rx: fclean exec

.PHONY: all clean fclean re bonus exe rp


# -->┊( EXE TEST RULES )
exe: all
	./minishell

exeval: exec
	$(VAL) $(FDFLAGS) $(SUPP) ./minishell

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
