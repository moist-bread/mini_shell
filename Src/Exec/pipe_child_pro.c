
#include "../../Inc/pipex.h"
#include "../../Inc/minishell.h"

void assign_pipe_fds(t_minishell minishell, t_pipe_data *pipex, int *redir_fd, int idx)
{
	int new_pipe[2];
	
	if (pipex->cur_pipe[0] > 2)
		close (pipex->cur_pipe[0]);
	if (redir_fd[0] > 2) // in redir
	{
    	printf("in redir --\n");
		pipex->cur_pipe[0] = redir_fd[0];
		if (pipex->next_pipe[0] > 2) // possible problem
			close(pipex->next_pipe[0]);
	}
	else // no in redir, input from pipe/stdin if prev cmd was redir out or cur is first
	{
    	printf("no in redir --\n");
		pipex->cur_pipe[0] = pipex->next_pipe[0];
		// pipex->next_pipe[0] = 0;
	}
	// am leaving fds open bc of this pipe PLEASE FIGURE IT OUT
	
    printf("create pipe --\n"); // standard case
	if (pipe(new_pipe) == -1)
		pipex_clean_up(minishell, 1); // pipe didnt create ABORT
	pipex->cur_pipe[1] = new_pipe[1];
	pipex->next_pipe[0] = new_pipe[0];
	if (redir_fd[1] > 2 || idx + 1 == pipex->cmd_n) // out redir or last cmd
	{
    	printf("out redir or last cmd --\n");
		if (pipex->cur_pipe[1] > 2)
			close (pipex->cur_pipe[1]);
		if (pipex->next_pipe[0] > 2 && idx + 1 == pipex->cmd_n)
			close (pipex->next_pipe[0]);
		pipex->cur_pipe[1] = redir_fd[1];
	}
}

void child_parse_and_exe(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx)
{
	(void)idx;
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
	if (pipex->next_pipe[0] > 2)
		close(pipex->next_pipe[0]);
	if (pipex->cur_pipe[0] > 2)
		dup2(pipex->cur_pipe[0], STDIN_FILENO);
	// else no working infile??
	if (pipex->cur_pipe[1] > 2)
		dup2(pipex->cur_pipe[1], STDOUT_FILENO);
	master_close();
	
	// executing --
	if (execve(pipex->path, pipex->cmd, pipex->env) == -1)
		pipex_clean_up(minishell, 1); // fail execution ABORT
}

char	*get_path(t_minishell minishell, char *cmds)
{
	char	**path;
	char	*joined;
	char	*bar;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (ft_strdup(cmds));
	i = -1;
	while (path[++i])
	{
		bar = ft_strjoin(path[i], "/");
		if (!bar)
			pipex_clean_up(minishell, 1); // fail alloc ABORT
		joined = ft_strjoin(bar, cmds);
		free(bar);
		if (!joined)
			pipex_clean_up(minishell, 1); // fail alloc ABORT
		if (access(joined, F_OK) == 0)
			return (free_split(path), joined);
		free(joined);
	}
	return (free_split(path), ft_strdup(cmds));
}
