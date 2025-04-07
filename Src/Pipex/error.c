/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:53:44 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/07 14:19:23 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

void	ft_error_file(t_pipex *pipex, char *s)
{
	perror(s);
	master_close();
	free_split(pipex->cmds);
	free(pipex->path);
	free(pipex->pid);
	exit(1);
}

void	ft_error(char *s)
{
	perror(s);
	master_close();
	exit(1);
}

void	ft_error_execve(t_pipex *pipex, char *s)
{
	perror(s);
	master_close();
	if (access(pipex->path, F_OK) < 0)
	{
		free_split(pipex->cmds);
		free(pipex->path);
		free(pipex->pid);
		exit(127);
	}
	else if (access(pipex->path, X_OK) < 0)
	{
		free_split(pipex->cmds);
		free(pipex->path);
		free(pipex->pid);
		exit(126);
	}
}

void	wait_pid(t_pipex *pipex)
{
	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], &pipex->status, 0);
}

void	master_close(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}
