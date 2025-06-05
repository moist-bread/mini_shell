/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:51:42 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 14:17:15 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static bool	ft_stronly(char *str, const char *find);

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
		pdata->cur_pipe[0] = redir_fd[0];
		safe_close(pdata->next_pipe);
	}
	else
		pdata->cur_pipe[0] = pdata->next_pipe;
	if (pipe(new_pipe) == -1)
		return (perror("pipe"), minishell_clean(ms, 1));
	pdata->cur_pipe[1] = new_pipe[1];
	pdata->next_pipe = new_pipe[0];
	if (redir_fd[1] > 2 || idx + 1 == pdata->cmd_n)
	{
		close(pdata->cur_pipe[1]);
		pdata->cur_pipe[1] = redir_fd[1];
		if (idx + 1 == pdata->cmd_n)
			close(pdata->next_pipe);
	}
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

	if (!*cmd || ft_stronly(cmd, "./"))
		return (ft_strdup(cmd));
	path = ft_split(get_env("PATH", ms.env), ':');
	if (!path)
		return (ft_strdup(cmd));
	i = -1;
	while (path[++i])
	{
		bar = ft_strjoin(path[i], "/");
		if (!bar)
			return (NULL);
		joined = ft_strjoin(bar, cmd);
		free(bar);
		if (!joined)
			return (NULL);
		if (access(joined, F_OK) == 0)
			return (free_split(path), joined);
		free(joined);
	}
	return (free_split(path), ft_strdup(cmd));
}

/// @brief Checks if STR only contains characters from FIND
/// @param str String to be checked 
/// @param find String containing all "allowed" characters
/// @return true if it only contains chars in FIND, else false
static bool	ft_stronly(char *str, const char *find)
{
	int	i;

	if (!*str)
		return (false);
	i = -1;
	while (str[++i])
		if (!ft_strchr(find, str[i]))
			return (false);
	return (true);
}

/// @brief Displays an error message and determines the exit status
/// @param path Path for command, to determine its existance
/// @return Exit status after execve() failure
int	error_code_for_exec(char *path)
{
	DIR	*dir;

	if (access(path, F_OK) < 0)
	{
		if (ft_strchr(path, '/'))
			return (ft_printf_fd(2, "%s: " M_NO_SUCH, path), 127);
		return (ft_printf_fd(2, "%s: command not found\n", path), 127);
	}
	else if (access(path, X_OK) < 0)
	{
		if (ft_strchr(path, '/'))
			return (ft_printf_fd(2, "%s: Permission denied\n", path), 126);
		return (ft_printf_fd(2, "%s: command not found\n", path), 127);
	}
	else if (ft_strchr(path, '/'))
	{
		dir = opendir(path);
		if (dir)
			return (closedir(dir), ft_printf_fd(2, "%s: Is a directory\n",
					path), 126);
		return (ft_printf_fd(2, "%s: " M_NO_SUCH, path), 127);
	}
	else
		return (ft_printf_fd(2, "%s: command not found\n", path), 127);
	return (0);
}
