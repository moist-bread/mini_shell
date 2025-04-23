
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
// If There Redir, Right is Arg, Check if next after Arg is Redir.
// If is Redir do the normal, if not check if is Pipe,
// If is Pipe start over.
// -------------------------------------------------------------------------------------------------|

// CHECKS ERROR

// Check what is after here_doc, strncmp, if for redirs ou pipe Error the syntax - Done
// If there is no space between quotes is considered 1 token: - Done
// Example: "easd"'O'""
// Get ridof len in working quotes and do a funciton that gets me the lenght in get word; - Done
// Implement in split that needs to split spaces and tabs in the same String; - Done
// This CMD:  >> banana cmd banana
// Needs to be REDIR ARG CMD ARG but is doing REDIR ARG ARG ARG - Dont know what to do;
// In the tree the last node redir is over writig the prrevious ones;

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
	LIM,
	REDIR_IN,
	REDIR_HERE_DOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	BUILT_IN,
}						t_node_type;

/// @param cmd_n Amount of cmds
/// @param cur_pipe Stores IN fd and OUT fd
/// @param next_pipe Read end of created pipe
/// @param pid Stores child process ids
/// @param cmd Command and its arguments
/// @param path Path to said command
/// @param env Environment
typedef struct s_pipe_data
{
	int					cmd_n;
	int					cur_pipe[2];
	int					next_pipe;
	int					*pid;
	char				**cmd;
	char				*path;
	char				**env;
}						t_pipe_data;

/// @brief Place where the content of t_node_type is stored
/// @param cmd (char *) Main command to be executed
/// @param args (char **) Versalite cmd arguments
/// @param pipe (t_pipe_data) Needed for pipe execution
/// @param file (char *) String for needed Infile/Outfile
/// @param limiter (char *) Limiter string for here_doc
typedef struct s_node_cont
{
	char				*cmd;
	char				**args;
	char				pipe_c;
	t_pipe_data			pipe;
	char				*file;
	char				*limiter;
}						t_node_cont;

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

// ------------------------PARSING----------------------------

// TOKENS

void	tokenadd_back(t_token **tklst, t_token *newtk);
void	tokenadd_front(t_token **tklst, t_token *newtk);
t_token	*newtoken(char *cont);
t_token	*create_tokens(char *input);
void	place_token(char *input, t_token **head);
void	print_tokens(t_token *tokens);
void	clear_token_lst(t_token	*token);
bool	is_token(t_token *token);

// TREE UTILS

void		print_tree(t_tree_node *tree_node, int depth, char *side);
void   		tree_apply_print(t_tree_node *root, int depth, char *side);
t_tree_node	*newtreenode(t_node_cont cont);
void		create_tree(t_token *tokens);
t_node_cont	assign_tree_cont(t_token *token);
void		if_command(t_token *tokens, t_tree_node *cmd_node);
void		place_treenode(t_token *tokens, t_tree_node **root, bool pipe);
void		free_tree_node_cont(t_node_cont cont);
void		free_tree(t_tree_node *tree_head);
void		tree_cont_init(t_node_cont *cont);
t_token		*iteri_till_pipe(t_token *token);
char		**tree_alloc_args(t_token *token);

// ASSIGN TYPES

void	assign_type_token(t_token *token);
void	assign_name(int type);
void	assigns_types(t_token *token);
void	assigns_built_in(t_token *token);
void	assigns_cmd_or_arg(t_token *token);

// UTILS

char	*add_spaces(char *input);
int		space_length(char *input);
char	*readinput(char	*input);
char	*space_put(char *input, int len);

// CHECKS

void	check_quotes(char *input);
void	master_check(t_token *token);

// ERRORS

void	ft_error_check(t_token *token);

// SPLIT UTILS

char	**cracked_split(char const *s);
int		word_len(char const *s);
int		skip_quote(const char *s);
void	word_runner(const char **s);
bool	is_sep(char c);

// char	*merge_adjacent_segments(char *input);
// void	check_double_pipe(int *j, int *i, char *dest);
// void	checks_here_doc(t_token	*token);
// char	**cracked_split(char const *s, char c);
// void	working_quote(char const *s, int *len, char c);
// char	*extract_single_quote(const char *s, int len);
// int		handle_single_quote(const char **s);


// --------------------------EXECUTION--------------------------

void	minishell_struct_init(t_minishell *minis, char **env);

// MATRIX UTILS

char	**matrix_add_front(char *add, char **original);
size_t	ft_matrixlen(char **matrix);
char	**matrix_dup_char(char **original_matrix);
void	free_matrix(void **matrix, int max);

// PIPE PROCESS

void	pipex_process(t_minishell *minishell, t_tree_node *tree_head,
		t_pipe_data *pipex);
void	read_and_exe_pipe_tree(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex, int idx);
void	execute_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx);
void	multi_proc_wait(t_pipe_data *pipex, int *status);
void	pipex_clean_up(t_minishell minishell, int status);

// PIPE REDIR HANDLER

void	redir_handler(t_minishell minishell, t_tree_node *cmd_node, int *in, int *out);
int		here_doc_redir(char *limiter);
void	master_close(void);

// PIPE CHILD PROCESS

void	assign_pipe_fds(t_minishell minishell, t_pipe_data *pipex, int *redir_fd, int idx);
void	child_parse_and_exe(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex);
char	*get_path(t_minishell minishell, char *cmds);
int		error_code_for_exec(t_pipe_data *pipex);

// ENV UTILS
char	*get_env(char *search, char **env);
char	**env_add_front(char *add, char **original);

#endif //MINISHELL_H