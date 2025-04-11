

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
