
#include "../../Inc/minishell.h"

static void	pipe_init(t_minishell *ms, t_pipe_data *pdata);

/// @brief Creates the pipe execution process and gets its exit status
/// @param minishell Overarching Minishell Structure
/// @param node Current pipe node to be executed
void	pipe_process(t_minishell *minishell, t_tree_node *node)
{
	int	id;

	ft_printf("\nEntering pipe pro\n");
	pipe_init(minishell, &node->cont.pipe);
	id = fork();
	if (id < 0)
		minishell_clean(*minishell, 1); // fail fork abort WITHOUT EXIT
	if (id == 0)
	{
		init_sigact(minishell, 'C');
		multi_here_doc_handler(*minishell, &node->cont.pipe);
		read_and_exe_pipe_tree(*minishell, minishell->tree_head,
			&node->cont.pipe, 0);
	}
	init_sigact(minishell, 'I');
	process_waiting(1, &id, &minishell->exit_status);
	init_sigact(minishell, 'P');
}

static void	pipe_init(t_minishell *ms, t_pipe_data *pdata)
{
	t_tree_node	*node;
	int			pipe_n;

	node = ms->tree_head;
	pipe_n = 1;
	while (node && node->type == PIPE)
	{
		pipe_n++;
		node = node->right;
	}
	pdata->cmd_n = pipe_n;
	pdata->pid = ft_calloc(pipe_n, sizeof(int));
	if (!pdata->pid)
		return ; // explode
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
/// @param node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void	setup_pipe_cmd(t_minishell minishell, t_tree_node *node,
		t_pipe_data *pdata, int idx)
{
	int	redir[2];

	ft_printf("\nEntering setup pipe cmd\n\n");

	// step 1: check redir and open needed --
	printf("step 1 --\n");
	redir[0] = 0;
	redir[1] = 1;
	redir_handler(node, &redir[0], &redir[1]);
	if (pdata->here_docs[idx] > 2)
	{
		if (redir[0] > 2)
			close(redir[0]);
		redir[0] = pdata->here_docs[idx];
	}
	
	// step 2: create pipe and assign fds --
	printf("step 2 --\n");
	assign_pipe_fds(minishell, pdata, redir, idx);

	// step 3: child pro, parse, dup execute --
	printf("step 3 --\n");
	pdata->pid[idx] = fork();
	if (pdata->pid[idx] < 0)
	{
		minishell_clean(minishell, 1); // fail fork ABORT?
	}
	if (pdata->pid[idx] == 0)
	{
		if (redir[0] == -1 || redir[1] == -1)
			minishell_clean(minishell, 1);
		if (node->type == CMD)
			cmd_parse_and_exe(minishell, node, pdata->cur_pipe);
		else if (node->type == BUILT_IN)
			minishell_clean(minishell, 0); // put built ins here
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
