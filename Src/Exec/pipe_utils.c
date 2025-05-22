
#include "../../Inc/minishell.h"

/// @brief Creates a pipe and assigns it, and or the existing redirs,
/// to the PDATA struct
/// @param ms Overarching Minishell Structure
/// @param pdata Struct used for the execution of pipes
/// @param redir_fd Redirection fds associated with the current command
/// @param idx Index for the command to be executed
void	assign_pipe_fds(t_minishell ms, t_pipe_data *pdata, int *redir_fd,
		int idx)
{
	int	new_pipe[2];

	if (redir_fd[0] > 2)
	{
		printf("in redir --\n");
		pdata->cur_pipe[0] = redir_fd[0];
		if (pdata->next_pipe > 2)
			close(pdata->next_pipe);
	}
	else // no in redir
	{
		printf("no in redir --\n");
		pdata->cur_pipe[0] = pdata->next_pipe;
	}
	printf("create pipe --\n");
	if (pipe(new_pipe) == -1)
		return (perror("pipe"), minishell_clean(ms, 1));
	pdata->cur_pipe[1] = new_pipe[1];
	pdata->next_pipe = new_pipe[0];
	if (redir_fd[1] > 2 || idx + 1 == pdata->cmd_n) // out redir or last cmd
	{
		printf("out redir or last cmd --\n");
		close(pdata->cur_pipe[1]);
		pdata->cur_pipe[1] = redir_fd[1];
		if (idx + 1 == pdata->cmd_n)
			close(pdata->next_pipe);
	}
	printf("\nAFTER FDS\n\nredir_fd[0]: %d\nredir_fd[1]: %d\n", redir_fd[0],
		redir_fd[1]);
	printf("pdata->cur_pipe[0]: %d\npdata->cur_pipe[1]: %d\n",
		pdata->cur_pipe[0], pdata->cur_pipe[1]);
	printf("pdata->next_pipe: %d\n", pdata->next_pipe);
}

/// @brief Searches for the true path to the CMD program
/// @param ms Overarching Minishell Structure
/// @param cmd Command for which the path is being searched
/// @return String with the commands corresponding path
char	*get_path(t_minishell ms, char *cmd)
{
	char	**path;
	char	*joined;
	char	*bar;
	int		i;

	path = ft_split(get_env("PATH", ms.env), ':');
	if (!path)
		return (ft_strdup(cmd));
	i = -1;
	while (path[++i])
	{
		bar = ft_strjoin(path[i], "/");
		if (!bar)
			return (perror("malloc"), NULL);
		joined = ft_strjoin(bar, cmd);
		free(bar);
		if (!joined)
			return (perror("malloc"), NULL);
		if (access(joined, F_OK) == 0)
			return (free_split(path), joined);
		free(joined);
	}
	return (free_split(path), ft_strdup(cmd));
}

/// @brief Displays an error message and determines the exit status
/// @param path Path for command, to determine its existance
/// @return Exit status after execve() failure
int	error_code_for_exec(char *path)
{
	if (access(path, F_OK) < 0)
	{
		ft_printf_fd(2, "%s: command not found\n", path);
		return (127);
	}
	else if (access(path, X_OK) < 0)
	{
		if (ft_strchr(path, '/'))
		{
			ft_printf_fd(2, "%s: Permission denied\n", path);
			return (126);
		}
		ft_printf_fd(2, "%s: command not found\n", path);
		return (127);
	}
	return (0);
}
