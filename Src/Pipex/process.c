/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:00:03 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/07 14:19:38 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

void	write_to_pipe(char **av, char **env, t_pipex *pipex)
{
	close(pipex->fd[0]);
	pipex->cmds = ft_split_pipe(av[2], ' ');
	if (!pipex->cmds || !pipex->cmds[0])
		ft_error_file(pipex, "Error Pipex");
	pipex->path = get_path(pipex->cmds[0], env, 0);
	if (!pipex->path)
		ft_error_file(pipex, "Error Pipex");
	pipex->infile = open(av[1], O_RDWR, 0644);
	if (pipex->infile == -1)
		ft_error_file(pipex, "Error Pipex");
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	master_close();
	if (execve(pipex->path, pipex->cmds, env) == -1)
		ft_error_execve(pipex, "Error Pipex");
}

void	the_pipe(char **av, char **env, t_pipex *pipex)
{
	close(pipex->fd[1]);
	pipex->cmds = ft_split_pipe(av[3], ' ');
	if (!pipex->cmds || !pipex->cmds[0])
		ft_error_file(pipex, "Error Pipex");
	pipex->path = get_path(pipex->cmds[0], env, 0);
	if (!pipex->path)
		ft_error_file(pipex, "Error Pipex");
	pipex->outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->outfile == -1)
		ft_error_file(pipex, "Error Pipex");
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	master_close();
	if (execve(pipex->path, pipex->cmds, env) == -1)
		ft_error_execve(pipex, "Error Pipex");
}

char	*get_env(char *search, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], search, ft_strlen(search)) != 0)
		i++;
	if (env[i])
		return ((env[i] + ft_strlen(search)));
	return (NULL);
}

char	*get_path(char *cmds, char **env, int i)
{
	char	**path;
	char	*final_line;
	char	*bar;

	path = ft_split_pipe(get_env("PATH=", env), ':');
	if (!path)
		return (ft_strdup(cmds));
	i = 0;
	while (path[i++])
	{
		bar = ft_strjoin(path[i], "/");
		final_line = ft_strjoin(bar, cmds);
		free(bar);
		if (!final_line)
			break ;
		if (access(final_line, F_OK) == 0)
			return (free_split(path), final_line);
		free(final_line);
	}
	return (free_split(path), ft_strdup(cmds));
}

void	alloc_pid(int size, t_pipex *pipex)
{
	pipex->pid = ft_calloc(size, sizeof(int));
	if (!pipex->pid)
		ft_error("Error Pipex");
}
