
#include "../../Inc/minishell.h"

/// @brief Main function that creates the AST_Tree 
/// @param tokens Node from the token list
/// @param cont The content
void	create_tree(t_token *tokens)
{
	t_tree_node	*tree_node;
	
	// printf("Entered Create Tree\n");
	tree_node = NULL;
	place_treenode(tokens, &tree_node, false);
	tree_apply_print(tree_node, 0, "Root");
	printf("\n");
}

/// @brief Assigns the content to the right place in the struct
/// @param token Node from the token list
/// @param cont The content
/// @return The content with the right stuff inside
t_node_cont	assign_tree_cont(t_token *token)
{
	t_node_cont	cont;

	// printf("Entered Assign Tree Cont\n");
	ft_bzero(&cont, sizeof(t_node_cont));
	if (token && (token->type == CMD || token->type == BUILT_IN))
		cont.cmd = token->cont;
	else if (token && token->type == LIM)
		cont.limiter = token->cont;
	else if (token && token->prev && (token->prev->type == REDIR_IN \
	|| token->prev->type == REDIR_OUT || token->prev->type == REDIR_OUT_APPEND) \
	&& token->type == ARG)
		cont.file = token->cont;
	else if (token && token->type == PIPE)
		cont.pipe_c = *token->cont;
	else if (token && token->type == ARG)
		cont.args = tree_alloc_args(token);
	return (cont);
}

/// @brief This functions puts the new tree_node in the right place in the AST_Tree
/// @param tokens Node from the token list
/// @param root The first node of the AST_Tree
/// @param cont The content of the nodes of the AST_Tree
void	place_treenode(t_token *tokens, t_tree_node **root, bool pipe)
{
	t_token		*pipe_token;
	t_tree_node	*new_tree_node;
	t_node_cont	tree_cont;

	// printf("Entered Place Tree Node\n");
	pipe_token = NULL;
	tree_cont_init(&tree_cont);
	if (pipe == false)
		pipe_token = iteri_till_pipe(tokens);
	if (pipe_token && pipe_token->type == PIPE)
	{
		tree_cont = assign_tree_cont(pipe_token);
		new_tree_node = newtreenode(tree_cont);
		place_treenode(tokens, &new_tree_node->left, true);
		place_treenode(pipe_token->next, &new_tree_node->right, false);
		*root = new_tree_node;
	}
	else
	{
		tree_cont = assign_tree_cont(tokens);
		new_tree_node = newtreenode(tree_cont);
		if (new_tree_node->cont.cmd)
			if_command(tokens, new_tree_node);
		*root = new_tree_node;
	}
}
