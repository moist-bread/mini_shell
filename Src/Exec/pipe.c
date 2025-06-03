
#include "../../Inc/minishell.h"

static void	pipe_init(t_minishell *ms, t_pipe_data *pdata);
static void	read_and_exe_pipe_tree(t_minishell minishell,
				t_tree_node *tree_head, t_pipe_data *pdata, int idx);
static void	setup_pipe_cmd(t_minishell ms, t_tree_node *node,
				t_pipe_data *pdata, int idx);
static void	distribute_pipe_cmd(t_minishell ms, t_tree_node *node,
				t_pipe_data *pdata, int *redir);

/// @brief Creates the pipe execution process and gets its exit status
/// @param ms Overarching Minishell Structure
/// @param node Current pipe node to be executed
void	pipe_process(t_minishell *ms, t_tree_node *node)
{
	int	id;

	// ft_printf("\nEntering pipe pro\n");
	pipe_init(ms, &node->cont.pipe);
	id = fork();
	if (id < 0)
		return (error_msg_status("fork", &ms->exit_status, 1));
	init_sigact(ms, 'I');
	if (id == 0)
	{
		multi_here_doc_handler(*ms, &node->cont.pipe);
		read_and_exe_pipe_tree(*ms, ms->tree_head, &node->cont.pipe, 0);
		process_waiting(node->cont.pipe.cmd_n, node->cont.pipe.pid,
			&ms->exit_status);
		minishell_clean(*ms, ms->exit_status);
	}
	process_waiting(1, &id, &ms->exit_status);
	init_sigact(ms, 'P');
}

/// @brief Initializes the values in PDATA according to the TREE in MS
/// @param ms Overarching Minishell Structure
/// @param pdata Struct used for the execution of pipes
/// @return 0 on success, -1 on failure
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
		return (perror("malloc"), minishell_clean(*ms, 1));
	pdata->here_docs = ft_calloc(pipe_n, sizeof(int));
	if (!pdata->here_docs)
		return (perror("malloc"), minishell_clean(*ms, 1));
	pdata->env = &ms->env[ms->env_start];
}

/// @brief Recurcivelly checks and initiates the execution of all
/// commands in a pipe tree
/// @param minishell Overarching Minishell Structure
/// @param tree_head Current tree node of type PIPE to distribute from
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
static void	read_and_exe_pipe_tree(t_minishell minishell,
		t_tree_node *tree_head, t_pipe_data *pdata, int idx)
{
	if (tree_head->left && (tree_head->left->type == CMD
			|| tree_head->left->type == BUILT_IN))
		setup_pipe_cmd(minishell, tree_head->left, pdata, idx++);
	if (tree_head->right && (tree_head->right->type == CMD
			|| tree_head->right->type == BUILT_IN))
		setup_pipe_cmd(minishell, tree_head->right, pdata, idx++);
	else if (tree_head->right && tree_head->right->type == PIPE)
		read_and_exe_pipe_tree(minishell, tree_head->right, pdata, idx);
}

/// @brief Setups up redirections, pipes, and sends nodes for execution
/// @param ms Overarching Minishell Structure
/// @param node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
static void	setup_pipe_cmd(t_minishell ms, t_tree_node *node,
		t_pipe_data *pdata, int idx)
{
	int	redir[2];

	// ft_printf("\nEntering setup pipe cmd\n\n");
	// printf("step 1: check redirs --\n");
	redir[0] = 0;
	redir[1] = 1;
	redir_handler(&ms, node, &redir[0], &redir[1]);
	successful_redir_check(&redir[0], &redir[1], pdata->here_docs[idx]);
	// printf("step 2: create pipe and assign fds --\n");
	assign_pipe_fds(ms, pdata, redir, idx);
	// printf("step 3: child pro, parse, dup exec --\n");
	pdata->pid[idx] = fork();
	if (pdata->pid[idx] < 0)
		return (perror("fork"), minishell_clean(ms, 1));
	if (pdata->pid[idx] == 0)
		distribute_pipe_cmd(ms, node, pdata, redir);
	// printf("step 4: parent close --\n");
	safe_close(pdata->cur_pipe[1]);
	pdata->cur_pipe[1] = 1;
	safe_close(pdata->cur_pipe[0]);
	pdata->cur_pipe[0] = 0;
}

/// @brief Sends the pipe process to execute a CMD or BUILT_IN according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
/// @param redir redir fds,
///	redir[0] is the IN redirection and redir[1] is the OUT redirection
static void	distribute_pipe_cmd(t_minishell ms, t_tree_node *node,
		t_pipe_data *pdata, int *redir)
{
	init_sigact(&ms, 'D');
	if (redir[0] == -1 || redir[1] == -1)
		minishell_clean(ms, 1);
	if (!node->cont.cmd)
		minishell_clean(ms, 0);
	if (node->type == CMD)
		cmd_parse_and_exe(ms, node, pdata->cur_pipe);
	else if (node->type == BUILT_IN)
	{
		built_in_exe(&ms, node, pdata->cur_pipe[1]);
		minishell_clean(ms, ms.exit_status);
	}
}
