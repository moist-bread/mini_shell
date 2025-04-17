
#include "../../Inc/minishell.h"

/// @brief Creates a pipe and assigns it, and or the existing redirs, to the PIPEX struct
/// @param minishell Overarching Minishell Structure
/// @param pipex Struct used for the execution of pipes
/// @param redir_fd Redirection fds associated with the current command
/// @param idx Index for the command to be executed
void assign_pipe_fds(t_minishell minishell, t_pipe_data *pipex, int *redir_fd, int idx)
{
	int new_pipe[2];
	
	if (redir_fd[0] > 2) // in redir
	{
    	printf("in redir --\n");
		pipex->cur_pipe[0] = redir_fd[0];
		if (pipex->next_pipe > 2) // possible problem
			close(pipex->next_pipe);
	}
	else // no in redir, input from pipe/stdin if prev cmd was redir out or cur is first
	{
    	printf("no in redir --\n");
		pipex->cur_pipe[0] = pipex->next_pipe;
	}
    printf("create pipe --\n"); // standard case
	if (pipe(new_pipe) == -1)
		pipex_clean_up(minishell, 1); // pipe didnt create ABORT
	pipex->cur_pipe[1] = new_pipe[1];
	pipex->next_pipe = new_pipe[0];
	if (redir_fd[1] > 2 || idx + 1 == pipex->cmd_n) // out redir or last cmd
	{
    	printf("out redir or last cmd --\n");
		close (pipex->cur_pipe[1]);
		pipex->cur_pipe[1] = redir_fd[1];
		if (idx + 1 == pipex->cmd_n)
			close (pipex->next_pipe);
	}
	printf("\nAFTER FDS\n\nredir_fd[0]: %d\nredir_fd[1]: %d\n", redir_fd[0], redir_fd[1]);
	printf("pipex->cur_pipe[0]: %d\npipex->cur_pipe[1]: %d\n", pipex->cur_pipe[0], pipex->cur_pipe[1]);
	printf("pipex->next_pipe: %d\n", pipex->next_pipe);
}

/// @brief Parses the cmd information from CMD_NODE, dups needed fds, and executes said command
/// @param minishell Overarching Minishell Structure
/// @param cmd_node Current node of type CMD or BUILT_IN to be executed
/// @param pipex Struct used for the execution of pipes
void child_parse_and_exe(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex)
{
	// cmd parse --
	if (cmd_node->right)
		pipex->cmd = matrix_add_front(cmd_node->cont.cmd, cmd_node->right->cont.args);
	else
		pipex->cmd = matrix_add_front(cmd_node->cont.cmd, NULL);
	if(!pipex->cmd)
		pipex_clean_up(minishell, 1); // fail fork ABORT
	// path parse --
	pipex->path = get_path(minishell, pipex->cmd[0]);
	if (!pipex->path)
			pipex_clean_up(minishell, 1); // fail alloc ABORT	
	// dupping --
	if (pipex->cur_pipe[0] > 2)
		dup2(pipex->cur_pipe[0], STDIN_FILENO);
	if (pipex->cur_pipe[1] > 2)
		dup2(pipex->cur_pipe[1], STDOUT_FILENO);
	master_close();
	// executing --
	// ADD OPTION FOR BUILT IN EXEC
	if (execve(pipex->path, pipex->cmd, pipex->env) == -1)
		pipex_clean_up(minishell, error_code_for_exec(pipex)); // fail execution ABORT
}

/// @brief Searches for the true path to the CMD program
/// @param minishell Overarching Minishell Structure
/// @param cmd Command for which the path is being searched
/// @return String with the commands corresponding path
char	*get_path(t_minishell minishell, char *cmd)
{
	char	**path;
	char	*joined;
	char	*bar;
	int		i;

	path = ft_split(get_env("PATH", minishell.env), ':');
	if (!path)
		return (ft_strdup(cmd));
	i = -1;
	while (path[++i])
	{
		bar = ft_strjoin(path[i], "/");
		if (!bar)
			pipex_clean_up(minishell, 1); // fail alloc ABORT
		joined = ft_strjoin(bar, cmd);
		free(bar);
		if (!joined)
			pipex_clean_up(minishell, 1); // fail alloc ABORT
		if (access(joined, F_OK) == 0)
			return (free_split(path), joined);
		free(joined);
	}
	return (free_split(path), ft_strdup(cmd));
}

/// @brief Displays an error message and determines the exit status
/// @param pipex Struct used for the execution of pipes
/// @return Exit status after execve() failure
int	error_code_for_exec(t_pipe_data *pipex)
{
	if (access(pipex->path, F_OK) < 0)
	{
		// make an error message function
		return(127);
	}
	else if (access(pipex->path, X_OK) < 0)
	{
		// make an error message function
		return(126);
	}
	return (0);
}
