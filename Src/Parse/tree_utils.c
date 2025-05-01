
#include "../../Inc/minishell.h"

t_tree_node	*newtreenode(t_node_cont cont)
{
	t_tree_node	*newnode;

	newnode = ft_calloc(1, sizeof(t_tree_node));
	if (!newnode)
		return (NULL);
	newnode->cont = cont;
	newnode->prev = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}

void	tree_cont_init(t_node_cont *cont)
{
	cont->cmd = NULL;
	cont->args = NULL;
	cont->pipe.cmd_n = 0;
	cont->pipe.cur_pipe[0] = 0;
	cont->pipe.cur_pipe[1] = 1;
	cont->pipe.next_pipe = 0;
	cont->pipe.pid = NULL;
	cont->pipe.cmd = NULL;
	cont->pipe.path = NULL;
	cont->pipe.env = NULL;
	cont->file = NULL;
	cont->limiter = NULL;
}

void	free_tree(t_tree_node *tree_head)
{
	if (tree_head->left)
		free_tree(tree_head->left);
	if (tree_head->right)
		free_tree(tree_head->right);
	free_tree_node_cont(tree_head->cont);
	free(tree_head);
	tree_head = NULL;
}

void	free_tree_node_cont(t_node_cont cont)
{
	if (cont.args)
		free_split(cont.args);
	if (cont.cmd)
		free(cont.cmd);
	if (cont.pipe.pid)
		free(cont.pipe.pid);
	if (cont.pipe.cmd)
		free_split(cont.pipe.cmd);
	if (cont.pipe.path)
		free(cont.pipe.path);
	if (cont.file)
		free(cont.file);
	if (cont.limiter)
		free(cont.limiter);
	if (cont.limiter)
		free(cont.limiter);
}
