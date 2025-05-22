
#include "../../Inc/minishell.h"

static int	pipe_init(t_minishell *ms, t_pipe_data *pdata);
static void	distribute_pipe_cmd(t_minishell ms, t_tree_node *node,
				t_pipe_data *pdata, int *redir);

/// @brief Creates the pipe execution process and gets its exit status
/// @param minishell Overarching Minishell Structure
/// @param node Current pipe node to be executed
void	pipe_process(t_minishell *minishell, t_tree_node *node)
{
	int	id;

	ft_printf("\nEntering pipe pro\n");
	if (pipe_init(minishell, &node->cont.pipe) == -1)
		return (error_msg_status("malloc", &minishell->exit_status, 1));
	init_sigact(minishell, 'I');
	id = fork();
	if (id < 0)
		return (error_msg_status("fork", &minishell->exit_status, 1));
	if (id == 0)
	{
		multi_here_doc_handler(*minishell, &node->cont.pipe);
		read_and_exe_pipe_tree(*minishell, minishell->tree_head,
			&node->cont.pipe, 0);
		process_waiting(node->cont.pipe.cmd_n, node->cont.pipe.pid,
			&minishell->exit_status);
		minishell_clean(*minishell, minishell->exit_status);
	}
	process_waiting(1, &id, &minishell->exit_status);
	init_sigact(minishell, 'P');
}

void	error_msg_status(char *message, int *status, int value)
{
	*status = value;
	printf("valor: %d\n", value);
	if (message)
		perror(message);
}

/// @brief Initializes the values in PDATA according to the TREE in MS
/// @param ms Overarching Minishell Structure
/// @param pdata Struct used for the execution of pipes
static int	pipe_init(t_minishell *ms, t_pipe_data *pdata)
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
		return (-1);
	pdata->here_docs = ft_calloc(pipe_n, sizeof(int));
	if (!pdata->here_docs)
		return (-1);
	pdata->env = &ms->env[ms->env_start];
	return (0);
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
/// @param minishell Overarching Minishell Structure
/// @param node Current node of type CMD or BUILT_IN to be executed
/// @param pdata Struct used for the execution of pipes
/// @param idx Index for the command to be executed
void	setup_pipe_cmd(t_minishell minishell, t_tree_node *node,
		t_pipe_data *pdata, int idx)
{
	int	redir[2];

	ft_printf("\nEntering setup pipe cmd\n\n");
	printf("step 1: check redir and open needed --\n");
	redir[0] = 0;
	redir[1] = 1;
	redir_handler(node, &redir[0], &redir[1]);
	successful_redir_check(&redir[0], &redir[1], pdata->here_docs[idx]);
	printf("step 2: create pipe and assign fds --\n");
	assign_pipe_fds(minishell, pdata, redir, idx);
	printf("step 3: child pro, parse, dup execute --\n");
	pdata->pid[idx] = fork();
	if (pdata->pid[idx] < 0)
		return (perror("fork"), minishell_clean(minishell, 1));
	if (pdata->pid[idx] == 0)
		distribute_pipe_cmd(minishell, node, pdata, redir);
	printf("step 4: parent close what needs to be closed --\n");
	if (pdata->cur_pipe[1] > 2)
		close(pdata->cur_pipe[1]);
	pdata->cur_pipe[1] = 1;
	if (pdata->cur_pipe[0] > 2)
		close(pdata->cur_pipe[0]);
	pdata->cur_pipe[0] = 0;
}

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
