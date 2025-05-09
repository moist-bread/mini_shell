
#include "../../Inc/minishell.h"

static void	pipe_init(t_minishell *ms, t_pipe_data *pdata);

/// @brief Creates the pipe execution process and gets its exit status
/// @param minishell Overarching Minishell Structure
/// @param pdata Struct used for the execution of pipes
void	pipe_process(t_minishell *minishell, t_pipe_data *pdata)
{
	int	id;

	ft_printf("\nEntering pipe pro\n");
	pipe_init(minishell, pdata);
	id = fork();
	if (id < 0)
		minishell_clean(*minishell, 1); // fail fork abort WITHOUT EXIT
	if (id == 0)
		read_and_exe_pipe_tree(*minishell, minishell->tree_head, pdata, 0);
	process_waiting(1, &id, &minishell->exit_status);
}

static void	pipe_init(t_minishell *ms, t_pipe_data *pdata)
{
	t_tree_node	*node;
	int			pipe_n;

	node = ms->tree_head;
	pipe_n = 1;
	while (node->type == PIPE)
	{
		pipe_n++;
		node = node->right;
	}
	pdata->cmd_n = pipe_n;
	pdata->pid = ft_calloc(pipe_n, sizeof(int));
	pdata->env = &ms->env[ms->env_start];
}

/// @brief Recurcivelly checks and initiates the execution of all
/// commands in a pipe tree
/// @param minishell Overarching Minishell Structure
/// @param tree_head Current tree node of type PIPE to distribute from
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void	read_and_exe_pipe_tree(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pdata, int idx)
{
	if (tree_head->left && tree_head->left->type == CMD) // ADD BUILT IN
		setup_pipe_cmd(minishell, tree_head->left, pdata, idx++);
	if (tree_head->right && tree_head->right->type == CMD)
		setup_pipe_cmd(minishell, tree_head->right, pdata, idx++);
	else if (tree_head->right && tree_head->right->type == PIPE)
		read_and_exe_pipe_tree(minishell, tree_head->right, pdata, idx);
	process_waiting(pdata->cmd_n, pdata->pid, &minishell.exit_status);
	master_close();
	minishell_clean(minishell, minishell.exit_status);
}

/// @brief Setups up redirections, pipes, and sends nodes for execution
/// @param minishell Overarching Minishell Structure
/// @param cmd_node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void	setup_pipe_cmd(t_minishell minishell, t_tree_node *cmd_node,
		t_pipe_data *pdata, int idx)
{
	int	redir[2];

	ft_printf("\nEntering setup pipe cmd\n\n");
	// step 1: check redir and open needed --
	printf("step 1 --\n");
	redir[0] = 0;
	redir[1] = 1;
	redir_handler(minishell, cmd_node, &redir[0], &redir[1]);
	// step 2: create pipe and assign fds --
	printf("step 2 --\n");
	assign_pipe_fds(minishell, pdata, redir, idx);
	// step 3: child pro, parse, dup execute --
	printf("step 3 --\n");
	pdata->pid[idx] = fork(); // couldnt test pipes bc of unalloced array
	if (pdata->pid[idx] < 0)
	{
		minishell_clean(minishell, 1); // fail fork ABORT?
	}
	if (pdata->pid[idx] == 0)
	{
		if (redir[0] == -1 || redir[1] == -1)
			minishell_clean(minishell, 1);
		child_parse_and_exe(minishell, cmd_node, pdata);
	}
	// step 4: parent close what needs to be closed --
	printf("step 4 --\n");
	if (pdata->cur_pipe[1] > 2)
		close(pdata->cur_pipe[1]);
	pdata->cur_pipe[1] = 1;
	if (pdata->cur_pipe[0] > 2)
		close(pdata->cur_pipe[0]);
	pdata->cur_pipe[0] = 0;
}
