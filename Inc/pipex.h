/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:47:11 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/16 17:41:37 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <limits.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include "minishell.h"

typedef struct s_pipex
{
	int		*pid;
	int		fd[2];
	char	**cmds;
	char	*path;
	int		infile;
	int		outfile;
	int		status;
}			t_pipex;

typedef struct s_pipex_b
{
	int		*pid;
	int		fd[2];
	char	**cmds;
	char	*path;
	char	**env;
	int		cmdn;
	int		infile;
	int		outfile;
	int		hdfd;
	int		status;
}			t_pipex_b;

// HERE_DOC
void	is_here_doc(t_pipex_b *pipex_b, char **av);
void	if_here_doc(t_pipex_b *pipex_b, char **av, int ac, int *i);

// PROCESS
void	alloc_pid_bonus(int size, t_pipex_b *pipex_b);
void	loop_pipes(t_pipex_b *pipex_b, char **av, int *i);
void	exec_func(t_pipex_b *pipex_b, char **av, int i);
void	the_output(t_pipex_b *pipex_b, char **av, int i);

// ERROR
void	ft_error_file_bonus(t_pipex_b *pipex_b, char *s);
void	ft_error_execve_bonus(t_pipex_b *pipex_b, char *s);

// UTILS
void	wait_pid_loop(t_pipex_b *pipex_b);
void	create_fork(t_pipex_b *pipex_b, int i);



// PROCESS FUNC
void	write_to_pipe(char **av, char **env, t_pipex *pipex);
void	the_pipe(char **av, char **env, t_pipex *pipex);

// GET FUNC
char	*get_path(char *cmds, char **env, int i);

// ERROR FUNC
void	ft_error_file(t_pipex *pipex, char *s);
void	ft_error(char *s);
void	ft_error_execve(t_pipex *pipex, char *s);

// UTILS FUNC
char	**ft_split_pipe(char const *s, char c);
void	master_close(void);
void	alloc_pid(int size, t_pipex *pipex);
void	wait_pid(t_pipex *pipex);
char	*get_env(char *search, char **env);

#endif