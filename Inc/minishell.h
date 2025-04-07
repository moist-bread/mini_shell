/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:22:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/07 17:20:44 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
/// @param in_pipe Stores
/// @param out_pipe
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
	REDIR_OUT,
	REDIR_OUT_APPEND,
	BUILT_IN,
}						t_node_type;

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
// put parsing prototypes here

// EXECUTION
// put execution prototypes here

// FILE NAME IN ALL CAPS
// functions in the file

#endif