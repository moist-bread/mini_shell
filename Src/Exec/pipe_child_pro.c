
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

	if (redir_fd[0] > 2) // in redir
	{
		printf("in redir --\n");
		pdata->cur_pipe[0] = redir_fd[0];
		if (pdata->next_pipe > 2) // possible problem
			close(pdata->next_pipe);
	}
	else // no in redir
	{
		printf("no in redir --\n");
		pdata->cur_pipe[0] = pdata->next_pipe;
	}
	printf("create pipe --\n"); // standard case
	if (pipe(new_pipe) == -1)
		minishell_clean(ms, 1); // pipe didnt create ABORT
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

/// @brief Parses the cmd information from NODE, dups needed fds,
/// and executes said command
/// @param ms Overarching Minishell Structure
/// @param node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
void	child_parse_and_exe(t_minishell ms, t_tree_node *node,
		t_pipe_data *pdata)
{
	// cmd parse --
	if (node->right)
		pdata->cmd = matrix_add_front(node->cont.cmd, node->right->cont.args);
	else
		pdata->cmd = matrix_add_front(node->cont.cmd, NULL);
	if (!pdata->cmd)
		minishell_clean(ms, 1); // fail fork ABORT
	// path parse --
	pdata->path = get_path(ms, pdata->cmd[0]);
	if (!pdata->path)
		minishell_clean(ms, 1); // fail alloc ABORT
	// dupping --
	if (pdata->cur_pipe[0] > 2)
		dup2(pdata->cur_pipe[0], STDIN_FILENO);
	if (pdata->cur_pipe[1] > 2)
		dup2(pdata->cur_pipe[1], STDOUT_FILENO);
	master_close();
	// executing --
	if (node->type == BUILT_IN && !master_distributer(&ms, node))
		minishell_clean(ms, ms.exit_status); // success, wrap up child pro
	else if (execve(pdata->path, pdata->cmd, pdata->env) == -1)
		minishell_clean(ms, error_code_for_exec(pdata->path)); // fail execve ABORT
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
			minishell_clean(minishell, 1); // fail alloc ABORT
		joined = ft_strjoin(bar, cmd);
		free(bar);
		if (!joined)
			minishell_clean(minishell, 1); // fail alloc ABORT
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
		free(path);
		// make an error message function
		return (127);
	}
	else if (access(path, X_OK) < 0)
	{
		free(path);
		// make an error message function
		return (126);
	}
	return (0);
}
