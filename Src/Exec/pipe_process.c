
#include "../../Inc/pipex.h"
#include "../../Inc/minishell.h"

void	pipex_process(t_minishell *minishell, t_tree_node *tree_head,
		t_pipe_data *pipex)
{	
	int id;
	int	exit_status;

	exit_status = 13;
	ft_printf("\nEntering pipe pro\n");
	id = fork();
	if (id < 0)
		pipex_clean_up(*minishell, 1); // fail fork abort WITHOUT EXIT
	if (id == 0)
		read_and_exe_pipe_tree(*minishell, tree_head, pipex, 0);
	waitpid(id, &exit_status, 0);
	if (WIFEXITED(exit_status))
		minishell->exit_status = WEXITSTATUS(exit_status);
}

void read_and_exe_pipe_tree(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex, int idx)
{
	if (tree_head->left && tree_head->left->type == CMD)
		execute_pipex_cmd(minishell, tree_head->left, pipex, idx++);
	if (tree_head->right && tree_head->right->type == CMD)
		execute_pipex_cmd(minishell, tree_head->right, pipex, idx++);
	else if (tree_head->right && tree_head->right->type == PIPE)
		read_and_exe_pipe_tree(minishell, tree_head->right, pipex, idx);
	multi_proc_wait(pipex, &minishell.exit_status);
	master_close();
	printf("\nexit status in pipex: %d\n", minishell.exit_status);
	pipex_clean_up(minishell, minishell.exit_status);
}

void	execute_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx)
{
	// EXECUTE THE COMMAND
	ft_printf("\nEntering execute pipe cmd\n\n");
	
	// step 1: check redir and open needed --
    printf("step 1 --\n");
	int	redir_fd[2];
	redir_fd[0] = 0;
	redir_fd[1] = 1;
	redir_handler(minishell, cmd_node, &redir_fd[0], &redir_fd[1]);	
	
	// step 2: create pipe and assign fds --
    printf("step 2 --\n");
	assign_pipe_fds(minishell, pipex, redir_fd, idx); // needs to know if its the last cmd

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

void	multi_proc_wait(t_pipe_data *pipex, int *status)
{
	int	i;
	int	exit_status;

	i = -1;
	*status = 0;
	while (++i < pipex->cmd_n)
		waitpid(pipex->pid[i], &exit_status, 0);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
}

void	pipex_clean_up(t_minishell minishell, int status)
{
	// add free env
	free_tree(minishell.tree_head);
	exit(status);
}
