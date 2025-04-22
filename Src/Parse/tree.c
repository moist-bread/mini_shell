

#include "../../Inc/minishell.h"

/// @brief Function that prints the Binary Tree
/// @param tree_node The First Node of the Tree
void	print_tree(t_tree_node *tree_node, int depth, char *side)
{
	int	i;

	printf("Entered Print Tree\n");
	i = -1;
	if(!tree_node)
		return ;
	while (++i <= depth)
		printf("\t");
	printf("Node Type: ");
	if (tree_node->cont.cmd)
		printf("CMD ");
	else if (tree_node->cont.file)
		printf("REDIR ");
	else if (tree_node->cont.limiter)
		printf("HEREDOC ");
	else if (tree_node->cont.args)
		printf("ARG ");
	else
		printf("PIPE ");
	printf("(%s)\n", side);

	i = -1;
	while (++i <= depth)
		printf("\t");
	
	if (tree_node->cont.cmd)
		printf("CMD: %s\n", tree_node->cont.cmd);
	else if (tree_node->cont.file)
		printf("FILE: %s\n", tree_node->cont.file);
	else if (tree_node->cont.limiter)
		printf("LIM: %s\n", tree_node->cont.limiter);
	else if (tree_node->cont.args)
	{
		printf("ARGS: ");
		for (int i = 0; tree_node->cont.args[i]; i++)
			printf("%s ", tree_node->cont.args[i]);
		printf("\n");
	}
	print_tree(tree_node->left, depth + 1, "Left");
	print_tree(tree_node->right, depth + 1, "Right");
}

/// @brief Main function that creates the binary tree 
/// @param tokens Node from the token list
/// @param cont The content
void	create_tree(t_token *tokens)
{
	t_tree_node	*tree_node;
	
	printf("Entered Create Tree\n");
	tree_node = NULL;
	place_treenode(tokens, &tree_node);
	print_tree(tree_node, 0, "Root");
}

/// @brief Assigns the content to the right place in the struct
/// @param token Node from the token list
/// @param cont The content
/// @return The content with the right stuff inside
t_node_cont	assign_tree_cont(t_token *token)
{
	int	i;
	t_node_cont	cont;

	printf("Entered Assign Tree Cont\n");
	ft_bzero(&cont, sizeof(t_node_cont));
	i = 0;
if (token && (token->type == CMD || token->type == BUILT_IN))
		cont.cmd = token->cont;
	else if (token && token->type == LIM)
		cont.limiter = token->cont;
	else if (token && token->prev && (token->prev->type == REDIR_IN \
	|| token->prev->type == REDIR_OUT || token->prev->type == REDIR_OUT_APPEND))
		cont.file = token->cont;
	else if (token && token->type == PIPE)
		return (cont);
	else if (token && token->type == ARG)
		cont.args = tree_alloc_args(token, &cont);
	return (cont);
}

/// @brief This functions puts the new tree_node in the right place in the binary tree
/// @param tokens Node from the token list
/// @param root The first node of the binary tree
/// @param cont The content of the nodes of the binary tree
void	place_treenode(t_token *tokens, t_tree_node **root)
{
	t_token		*pipe_token;
	t_tree_node	*new_tree_node;
	t_node_cont	tree_cont;

	printf("Entered Place Tree Node\n");
	tree_cont_init(&tree_cont);
	pipe_token = iteri_till_pipe(tokens);
	if (pipe_token && pipe_token->type == PIPE)
	{
		tree_cont = assign_tree_cont(tokens);
		new_tree_node = newtreenode(tree_cont);
		place_treenode(tokens, &new_tree_node->left);
		place_treenode(pipe_token->next, &new_tree_node->right);
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
