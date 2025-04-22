

#include "../../Inc/minishell.h"


/// @brief Function that prints the Binary Tree
/// @param root The First Node of the Tree
void	print_tree(t_tree_node *root)
{
	if(!root)
		return ;

}

/// @brief Main function that creates the binary tree 
/// @param tokens Node from the token list
/// @param cont The content
void	create_tree(t_token *tokens, t_node_cont *cont)
{
	t_tree_node	*tree_node;
	
	tree_node = NULL;
	tree_cont_init(cont);
	place_treenode(tokens, &tree_node, cont);
	print_tree(tree_node);

}

/// @brief Assigns the content to the right place in the struct
/// @param token Node from the token list
/// @param cont The content
/// @return The content with the right stuff inside
t_node_cont	*assign_tree_cont(t_token *token, t_node_cont *cont)
{
	int	i;

	i = 0;
	if (token && token->type == CMD)
		cont->cmd = token->cont;
	else if (token && token->type == LIM)
		cont->limiter = token->cont;
	else if (token && token->prev && (token->prev->type == REDIR_IN \
	|| token->prev->type == REDIR_OUT || token->prev->type == REDIR_OUT_APPEND))
		cont->file = token->cont;
	else if (token && token->type == PIPE)
		return (cont);
	else if (token && token->type == ARG)
		cont->args = tree_alloc_args(token, cont);
	return (cont);
}

/// @brief This functions puts the new tree_node in the right place in the binary tree
/// @param tokens Node from the token list
/// @param root The first node of the binary tree
/// @param cont The content of the nodes of the binary tree
void	place_treenode(t_token *tokens, t_tree_node **root, t_node_cont *cont)
{
	t_token		*temp;
	t_tree_node	*new_tree_node;
	t_node_cont *new_cont;

	temp = iteri_till_pipe(tokens);
	while(temp)
	{
		new_cont = assign_tree_cont(tokens, cont);
		new_tree_node = newtreenode(*new_cont);
		left_or_right(new_tree_node);
	}
}
