
#ifndef MINISHELL_H
# define MINISHELL_H

// NOTES: ANDRE

// char *input = "< infile cat | cat | "ls -l" > out"; 
// cracked slpit returns t_node just for basic token and sep is space.
// Nodes:
// 1 - "<"; 2 - "infile"; 3 - "cat"; 4 - "|"; 5 - "cat"; etc; 
// funcs that check the new list of tokens.
// Funcs:
// Check Pipes and redir for spaces, if they dont have it put space after and before
// Diverse check enquanto corro a lista the tokens;
// Assign types to the tokens;
// Func That will create the tree for varios Casos;

// -------------------------------------------------------------------------------------------------|

// First pipe initilize pipe data and put number of cmds.
// Other pipes just the type and the correspondant left and right nodes;
// If Pipe, Left always cmds;
// If Pipe, Right next Operator or The final cmds;
// If Cmd, Left Redir, Right Args "Flags e afins" 
// If Redir, Left Redir, cont the file name or LIMITER, 
// Consult on the .h for the Types of Redir;
// Check with rackel if is Build it for the correct Type;

// -------------------------------------------------------------------------------------------------|

// CHECKS ERROR

// Check what is after here_doc, strncmp, if for redirs ou pipe Error the syntax

// -------------------------------------------------------------------------------------------------|

// LIBS
# include "Libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// DEFINES
// colors
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define CYN "\e[0;36m"
# define DEF "\e[0m"

// STRUCTS

/// @param cmd_n Amount of cmds
/// @param cur_pipe Stores
/// @param next_pipe algo
/// @param pid Stores child process ids
/// @param cmd Command and its arguments
/// @param path Path to said command
/// @param env Environment
typedef struct s_pipe_data
{
	int					cmd_n;
	int					cur_pipe[2];
	int					next_pipe[2];
	int					*pid;
	char				**cmd;
	char				*path;
	char				**env;
}						t_pipe_data;

/// @brief Enumeration of all possible node types
/// @param CMD Commands
/// @param ARG Versatile arguments
/// @param PIPE |
/// @param REDIR_IN <
/// @param REDIR_HERE_DOC <<
/// @param LIM Arg after here_doc
/// @param REDIR_OUT >
/// @param REDIR_OUT_APPEND >>
/// @param BUILT_IN echo cd pwd export unset env exit
typedef enum s_node_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_HERE_DOC,
	LIM,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	BUILT_IN,
}						t_node_type;

/// @param type Node Type
/// @param cont Node Content
/// @param next Next Node
typedef struct s_token
{
	t_node_type			type;
	char				*cont;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

/// @brief Place where the content of t_node_type is stored
/// @param cmd (char *) Main command to be executed
/// @param args (char **) Versalite cmd arguments
/// @param pipe Structure needed for pipe execution
/// @param file (char *) String for needed Infile/Outfile
/// @param limiter (char *) Limiter string for here_doc
typedef struct s_node_cont
{
	char				*cmd;
	char				**args;
	t_pipe_data			pipe;
	char				*file;
	char				*limiter;
}						t_node_cont;

/// @brief Abstract Syntax Tree Node
/// @param type Node Type
/// @param cont Node Content
/// @param prev Previous tree node
/// @param left Left branch
/// @param right Right branch
typedef struct s_tree_node
{
	t_node_type			type;
	t_node_cont			cont;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

/// @brief Overarching Minishell Structure
/// @param tree_head Parsed Input Tree
/// @param env Environment
/// @param exit_status Exit Status of the latest process
typedef struct s_minishell
{
	t_tree_node			*tree_head;
	char				**env;
	int					exit_status;
}						t_minishell;

// TBD
// (to be determined) functions without a place yet

// PARSING

void	tokenadd_back(t_token **tklst, t_token *newtk);
void	tokenadd_front(t_token **tklst, t_token *newtk);
t_token	*newtoken(char *cont);
void	create_tokens(char *input);
char	*readinput(char	*input);
void	place_token(char *input, t_token **head);
void	print_tokens(t_token *tokens);
void	assign_type_token(t_token *token);
void	assign_name(int type);
void	check_types(t_token *token);
void	checks_built_in(t_token *token);
void	check_cmd_or_arg(t_token *token);
// char	**cracked_split(char const *s, char c);
// void	working_quote(char const *s, int *len, char c);
// char	*extract_single_quote(const char *s, int len);
// int		handle_single_quote(const char **s);

// TREE UTILS

t_tree_node	*newtreenode(t_node_cont cont);

// EXECUTION
// put execution prototypes here

// MATRIX UTILS

char	**matrix_add_front(char *add, char **original);
size_t	ft_matrixlen(char **matrix);
char	**matrix_dup_char(char **original_matrix);
void	free_matrix(void **matrix, int max);

// PIPE PROCESS

void	pipex_process(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex, int idx);
void	execute_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx);
void	multi_proc_wait(t_pipe_data *pipex, int *status);
void	pipex_clean_up(t_minishell minishell, int status);

// PIPE REDIR HANDLER

void redir_handler(t_minishell minishell, t_tree_node *cmd_node, int *in, int *out);
int	here_doc_redir(char *limiter);
void	master_close(void);

// PIPE CHILD PROCESS

void assign_pipe_fds(t_minishell minishell, t_pipe_data *pipex, int *redir_fd, int idx);
void child_parse_and_exe(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx);
char	*get_path(t_minishell minishell, char *cmds);

void	free_tree_node_cont(t_node_cont cont);
void	free_tree(t_tree_node *tree_head);
void	tree_cont_init(t_node_cont *cont);
// FILE NAME IN ALL CAPS
// functions in the file

#endif