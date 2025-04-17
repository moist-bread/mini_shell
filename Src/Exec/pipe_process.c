
#include "../../Inc/minishell.h"

/// @brief Creates the pipe execution process and gets its exit status
/// @param minishell Overarching Minishell Structure
/// @param pipex Struct used for the execution of pipes
void	pipex_process(t_minishell *minishell, t_pipe_data *pipex)
{	
	int id;

	ft_printf("\nEntering pipe pro\n");
	id = fork();
	if (id < 0)
		pipex_clean_up(*minishell, 1); // fail fork abort WITHOUT EXIT
	if (id == 0)
		read_and_exe_pipe_tree(*minishell, minishell->tree_head, pipex, 0);
	process_waiting(1, &id, &minishell->exit_status);
}

/// @brief Recurcivelly checks and initiates the execution of all commands in a pipe tree  
/// @param minishell Overarching Minishell Structure
/// @param tree_head Current tree node of type PIPE to distribute from
/// @param pipex Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void read_and_exe_pipe_tree(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex, int idx)
{
	if (tree_head->left && tree_head->left->type == CMD)
		setup_pipex_cmd(minishell, tree_head->left, pipex, idx++);
	if (tree_head->right && tree_head->right->type == CMD)
		setup_pipex_cmd(minishell, tree_head->right, pipex, idx++);
	else if (tree_head->right && tree_head->right->type == PIPE)
		read_and_exe_pipe_tree(minishell, tree_head->right, pipex, idx);
	process_waiting(pipex->cmd_n, pipex->pid, &minishell.exit_status);
	master_close();
	pipex_clean_up(minishell, minishell.exit_status);
}

/// @brief Setups up redirections, pipes, and sends nodes for execution
/// @param minishell Overarching Minishell Structure
/// @param cmd_node Current node of type CMD or BUILT_IN to be executed
/// @param pipex Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void	setup_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx)
{
	ft_printf("\nEntering setup pipe cmd\n\n");
	// step 1: check redir and open needed --
    printf("step 1 --\n");
	int	redir_fd[2];
	redir_fd[0] = 0;
	redir_fd[1] = 1;
	redir_handler(minishell, cmd_node, &redir_fd[0], &redir_fd[1]);	
	// step 2: create pipe and assign fds --
    printf("step 2 --\n");
	assign_pipe_fds(minishell, pipex, redir_fd, idx);
	// step 3: child pro, parse, dup execute --
    printf("step 3 --\n");
	pipex->pid[idx] = fork();
	if (pipex->pid[idx] < 0)
		pipex_clean_up(minishell, 1); // fail fork ABORT
	if (pipex->pid[idx] == 0)
		child_parse_and_exe(minishell, cmd_node, pipex);
	// step 4: parent close what needs to be closed --
    printf("step 4 --\n");
	if (pipex->cur_pipe[1] > 2)
		close(pipex->cur_pipe[1]);
	pipex->cur_pipe[1] = 1;
	if (pipex->cur_pipe[0] > 2)
		close (pipex->cur_pipe[0]);
	pipex->cur_pipe[0] = 0;
}

/// @brief Waits for the pids in IDS and stores it's exit status in STATUS
/// @param proc_n Amount of processes to wait for
/// @param ids Array containing the ids of said processes
/// @param status Pointer to var where to store the final exit status in
void	process_waiting(int proc_n, int *ids, int *status)
{
	int	i;
	int	exit_status;

	i = -1;
	*status = 0;
	while (++i < proc_n)
		waitpid(ids[i], &exit_status, 0);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
}

/// @brief Cleans all content from the MINISHELL struct
/// @param minishell Overarching Minishell Structure
/// @param status Process exit status
void	pipex_clean_up(t_minishell minishell, int status)
{
	if (minishell.tree_head)
		free_tree(minishell.tree_head);
	free_split(minishell.env);
	exit(status);
}
