/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:22:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/04 18:24:43 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBS
# include "Libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// DEFINES
// colors
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define CYN "\e[0;36m"
# define DEF "\e[0m"

// STRUCTS

typedef struct s_crossfd
{
	int					in_read;
	int					in_write;
	int					out_read;
	int					out_write;
}						t_crossfd;

/// @param cmd_n amount of cmds
/// @param fd stores infile fd, pipe fds, outfile fd
/// @param cmd commands and their parameters
/// @param paths paths to said cmds
/// @param pid stores child process ids
/// @param env environment
typedef struct s_pipe_data
{
	int					cmd_n;
	int					in_pipe[2];
	int					out_pipe[2];
	int					*pid;
	char				**cmd;
	char				*path;
	char				**env;
}						t_pipe_data;

typedef struct s_node_type
{
	bool				built_in;
	bool				cmd;
	bool				pipe;
	bool				here_doc;
	bool				redir;
	bool				expand;
	bool				and;
	bool				or;
}						t_node_type;

typedef struct s_node_cont
{
	char				**cmd;
	t_pipe_data			pipe;
	char				*limiter;
}						t_node_cont;

typedef struct s_tree_node
{
	t_node_type			type;
	t_node_cont			cont;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

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