
#include "../../Inc/minishell.h"

int cmd_redir_executer(t_minishell *ms, t_tree_node *node, int *in, int *out)
{
	int hd;

	hd = 0;
	single_here_doc_handler(*ms, node, &hd);
	*in = 0;
	*out = 1;
	redir_handler(node, in, out);
	if (*in == -1 || *out == -1)
	{
		if (*in > 2)
			close(*in);
		else if (*out > 2)
			close(*out);
		return (-1);
	}
	if (hd > 2)
	{
		if (*in > 2)
			close(*in);
		*in = hd;
	}
	return (0);
}

/// @brief Recurcivelly checks and opens all redirections associated with NODE
/// @param node Current tree node being checked for redirections
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
void	redir_handler(t_tree_node *node, int *in, int *out)
{
	if (!node->left) // no more redir
		return ;
	if (node->left->type == REDIR_IN) // IN <
	{
		if (*in > 2)
			close(*in);
		*in = open(node->left->cont.file, O_RDONLY);
	}
	else if (node->left->type == REDIR_OUT) // OUT >
	{
		if (*out > 2)
			close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (node->left->type == REDIR_OUT_APPEND) // APPEND OUT >>
	{
		if (*out > 2)
			close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	if (*in == -1 || *out == -1) // failed open
		return (perror(node->left->cont.file));
	if (node->left->left) // more redir
		redir_handler(node->left, in, out);
}
