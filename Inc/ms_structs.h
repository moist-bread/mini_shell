
#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

// STRUCTS

/// @param cmd_n Amount of cmds
/// @param cur_pipe Stores IN fd and OUT fd
/// @param next_pipe Read end of created pipe
/// @param here_docs stores the ids of
/// @param pid Stores child process ids
/// @param env Environment
typedef struct s_pipe_data
{
	int					cmd_n;
	int					cur_pipe[2];
	int					next_pipe;
	int					*here_docs;
	int					*pid;
	char				**env;
}						t_pipe_data;

/// @brief Enumeration of all possible node types
/// @param CMD Commands
/// @param ARG Versatile arguments
/// @param PIPE |
/// @param LIM Arg after here_doc
/// @param RED_IN <
/// @param RED_HD <<
/// @param RED_OUT >
/// @param RED_APP >>
/// @param BUILT_IN echo cd pwd export unset env exit
typedef enum s_node_type
{
	CMD,
	ARG,
	PIPE,
	LIM,
	RED_IN,
	RED_HD,
	RED_OUT,
	RED_APP,
	BUILT_IN,
}						t_node_type;

/// @param type Node Type
/// @param cont Node Content
/// @param next Next Node
typedef struct s_token
{
	t_node_type			type;
	char				*cont;
	bool				quote;
	struct s_token		*next;
	struct s_token		*prev; // MY FUNCTION
}						t_token;

/// @brief Place where the content of t_node_type is stored
/// @param cmd (char *) Main command to be executed
/// @param args (char **) Versalite cmd arguments
/// @param pipe (t_pipe_data) Needed for pipe execution
/// @param pipe_c (t_pipe_data) Needed for pipe execution
/// @param file (char *) String for needed Infile/Outfile
/// @param limiter (char *) Limiter string for here_doc
typedef struct s_node_cont
{
	char				*cmd;
	char				**args;
	char				pipe_c; // trash
	t_pipe_data			pipe;
	char				*file;
	char				*limiter; // MY FUNCTION
	bool				quote;
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
	int					env_start;
	int					exit_status;
}						t_minishell;

#endif // MS_STRUCTS_H
