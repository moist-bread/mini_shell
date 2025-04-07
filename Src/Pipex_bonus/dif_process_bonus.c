/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dif_process_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:47:18 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/07 14:20:41 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

void	is_here_doc(t_pipex_b *pipex_b, char **av)
{
	char	*cancer_line;

	alloc_pid_bonus(pipex_b->cmdn, pipex_b);
	pipex_b->hdfd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex_b->hdfd == -1)
		ft_error_file_bonus(pipex_b, "Error Pipex");
	ft_putstr_fd("> ", 1);
	cancer_line = get_next_line(0);
	while (cancer_line)
	{
		if (ft_strncmp(av[2], cancer_line, ft_strlen(av[2])) == 0)
			break ;
		ft_putstr_fd(cancer_line, pipex_b->hdfd);
		free(cancer_line);
		ft_putstr_fd("> ", 1);
		cancer_line = get_next_line(0);
	}
	if (cancer_line)
		free(cancer_line);
	close(pipex_b->hdfd);
	pipex_b->hdfd = open("here_doc", O_RDWR);
	if (pipex_b->hdfd == -1)
		ft_error_file_bonus(pipex_b, "Error Pipex");
	dup2(pipex_b->hdfd, STDIN_FILENO);
	close(pipex_b->hdfd);
}

void	if_here_doc(t_pipex_b *pipex_b, char **av, int ac, int *i)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex_b->outfile = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
		if (pipex_b->outfile == -1)
			return (ft_error("Error Pipex"));
		pipex_b->cmdn = ac - 4;
		is_here_doc(pipex_b, av);
		*i = 2;
	}
	else
	{
		pipex_b->outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (pipex_b->outfile == -1)
			return (ft_error("Error Pipex"));
		pipex_b->cmdn = ac - 3;
		alloc_pid_bonus(pipex_b->cmdn, pipex_b);
		pipex_b->infile = open(av[1], O_RDWR);
		dup2(pipex_b->infile, STDIN_FILENO);
		close(pipex_b->infile);
		*i = 1;
	}
}

void	loop_pipes(t_pipex_b *pipex_b, char **av, int *i)
{
	static int	j;

	if (pipe(pipex_b->fd) == -1)
		ft_error_file_bonus(pipex_b, "Error Pipex");
	create_fork(pipex_b, j);
	if (pipex_b->pid[j] == 0)
	{
		close(pipex_b->fd[0]);
		dup2(pipex_b->fd[1], STDOUT_FILENO);
		close(pipex_b->fd[1]);
		if (j++ == 0)
			if (access(av[1], F_OK | R_OK) < 0)
				return (ft_error_file_bonus(pipex_b, "Error Access File\n"));
		exec_func(pipex_b, av, *i);
	}
	else
	{
		close(pipex_b->fd[1]);
		dup2(pipex_b->fd[0], STDIN_FILENO);
		close(pipex_b->fd[0]);
	}
}

void	exec_func(t_pipex_b *pipex_b, char **av, int i)
{
	pipex_b->cmds = ft_split_pipe(av[i], ' ');
	if (!pipex_b->cmds || !pipex_b->cmds[0])
		ft_error_file_bonus(pipex_b, "Error Pipex");
	pipex_b->path = get_path(pipex_b->cmds[0], pipex_b->env, 0);
	if (!pipex_b->path)
		ft_error_file_bonus(pipex_b, "Error Pipex");
	master_close();
	if (execve(pipex_b->path, pipex_b->cmds, pipex_b->env) == -1)
		ft_error_execve_bonus(pipex_b, "Error Pipex");
}

void	the_output(t_pipex_b *pipex_b, char **av, int i)
{
	int	last_pid;

	last_pid = fork();
	if (last_pid == 0)
	{
		dup2(pipex_b->outfile, STDOUT_FILENO);
		close(pipex_b->outfile);
		exec_func(pipex_b, av, i);
	}
	else
		pipex_b->pid[pipex_b->cmdn - 1] = last_pid;
}
