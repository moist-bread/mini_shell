/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:22:02 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/03/25 17:08:12 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBS
// # include "Libft/libft.h"
# include <stdarg.h>
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

/// @param count amount of cmds
/// @param fd stores infile fd, pipe fds, outfile fd
/// @param cmd commands and their parameters
/// @param paths paths to said cmds 
/// @param pid stores child process ids
/// @param env environment
typedef struct s_pipe_data
{
	int		count;
	int		**fd;
	char	***cmd;
	char	**paths;
	int		*pid;
	char	**env;
}			t_pipe_data;

// TBD
// (to be determined) functions without a place yet

// PARSING
// put parsing prototypes here

// EXECUTION
// put execution prototypes here


// FILE NAME IN ALL CAPS
// functions in the file

#endif