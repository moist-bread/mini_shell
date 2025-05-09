
#include "../../Inc/minishell.h"

/// @brief Looks at the Input Tree sends it to the
/// corresponding executer
/// @param ms Overarching Minishell Structure
int	master_distributer(t_minishell *ms, t_tree_node *node)
{
	if (!node)
		return (1);
	printf(YEL "\nEntering master distributer" DEF "\n\n");
	if (node->type == PIPE)
		pipe_process(ms, &node->cont.pipe);
	if (node->type == CMD)
		command_process(ms, node);
	else if (node->type == BUILT_IN)
	{
		// MISSING REDIRS
		printf("is built in\n");
		if (!ft_strcmp("echo", node->cont.cmd))
			echo_built_in(ms, node);
		else if (!ft_strcmp("cd", node->cont.cmd))
			cd_built_in(ms, node); // coming soon
		else if (!ft_strcmp("pwd", node->cont.cmd))
			pwd_built_in(ms, node); // coming soon
		else if (!ft_strcmp("export", node->cont.cmd))
			export_built_in(ms, node);
		else if (!ft_strcmp("unset", node->cont.cmd))
			unset_built_in(ms, node);
		else if (!ft_strcmp("env", node->cont.cmd))
			env_built_in(ms, node);
		else if (!ft_strcmp("exit", node->cont.cmd))
			exit_built_in(ms, node);
	}
	return (0);
}

void	command_process(t_minishell *ms, t_tree_node *node)
{
	int	id;
	int	redir[2];

	printf(YEL "\nEntering Command Executer" DEF "\n\n");
	// step 1: check redir and open needed --
	printf("step 1 --\n");
	redir[0] = 0;
	redir[1] = 1;
	// handle heredoc and store it in an int
	redir_handler(*ms, node, &redir[0], &redir[1]);
	// if redir[0] != -1 && here_dod > 0  redir[0] = here doc
	// step 2: child pro, parse, dup execute --
	printf("step 2 --\n");
	id = fork();
	if (id < 0)
		minishell_clean(*ms, 1); // fail fork ABORT?
	if (id == 0 && (redir[0] == -1 || redir[1] == -1))
		minishell_clean(*ms, 1); // failed redir
	else if (id == 0)
		cmd_parse_and_exe(*ms, node, redir); // child exec
	if (redir[0] > 2)
		close(redir[0]);
	if (redir[1] > 2)
		close(redir[1]);
	process_waiting(1, &id, &ms->exit_status);
}

void	cmd_parse_and_exe(t_minishell ms, t_tree_node *node, int *redir)
{
	char	*path;
	int		status;

	// cmd parse --
	if (node->right)
		node->right->cont.args = matrix_add_front(node->cont.cmd,
				node->right->cont.args);
	else
		node->right->cont.args = matrix_add_front(node->cont.cmd, NULL);
	if (!node->right->cont.args)
		minishell_clean(ms, 1); // fail alloc ABORT
	// path parse --
	path = get_path(ms, node->right->cont.args[0]);
	if (!path)
		minishell_clean(ms, 1); // fail alloc ABORT
	// dupping --
	if (redir[0] > 2)
		dup2(redir[0], STDIN_FILENO);
	if (redir[1] > 2)
		dup2(redir[1], STDOUT_FILENO);
	master_close();
	// executing --
	if (execve(path, node->right->cont.args, &ms.env[ms.env_start]) == -1)
	{
		status = error_code_for_exec(path);
		free(path);
		minishell_clean(ms, status); // fail execve ABORT
	}
}
