
#include "../../Inc/minishell.h"

/// @brief Creates a new tree_node
/// @param cont The content of this new node 
/// @return The newly created node
t_tree_node	*newtreenode(t_node_cont cont)
{
	t_tree_node	*newnode;

	newnode = ft_calloc(1, sizeof(t_tree_node));
	if (!newnode)
		return (perror("malloc13"), NULL);
	newnode->cont = cont;
	newnode->prev = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}

/// @brief Inicializes the pipe_data struct
/// and the tree_node struct
/// @param cont The content of the content
void	tree_cont_init(t_node_cont *cont)
{
	cont->cmd = NULL;
	cont->args = NULL;
	cont->pipe.cmd_n = 0;
	cont->pipe.cur_pipe[0] = 0;
	cont->pipe.cur_pipe[1] = 1;
	cont->pipe.next_pipe = 0;
	cont->pipe.here_docs = NULL;
	cont->pipe.pid = NULL;
	cont->pipe.env = NULL;
	cont->file = NULL;
	cont->limiter = NULL;
}

/// @brief Frees the AST_Tree 
/// @param tree_head The root of the Tree
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

/// @brief Frees the content of witch tree node
/// @param cont The content
void	free_tree_node_cont(t_node_cont cont)
{
	if (cont.cmd)
		free(cont.cmd);
	if (cont.args)
		free_split(cont.args);
	if (cont.pipe.pid)
		free(cont.pipe.pid);
	if (cont.pipe.here_docs)
		free(cont.pipe.here_docs);
	if (cont.file)
		free(cont.file);
	if (cont.limiter)
		free(cont.limiter);
}

int	expander(t_token *curr, t_minishell *ms, t_token **head)
{
	char	**expanded;

	expanded = input_expander(curr->cont, *ms);
	if (!expanded)
	{
		syntax_clear(head);
		minishell_clean(*ms, 1);
	}
	curr = replace_expanded_token(head, curr, expanded);
	free_split(expanded);
	return (0);
}

void	syntax_clear(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		free(current->cont);
		free(current);
		current = next;
	}
	*token = NULL;
}

/// @brief Function that prints the AST_Tree
/// @param tree_node The First Node of the Tree
/// @param depth Where i am in the AST_Tree
/// @param side Left or Right
void	print_tree(t_tree_node *tree_node, int depth, char *side)
{
	if (!tree_node)
		return;
	for (int i = 0; i < depth; i++)
		printf("\t");
	assign_name(tree_node->type);
	printf(" (%s)\n", side);
	for (int i = 0; i < depth; i++)
		printf("\t");
	if (tree_node->cont.cmd)
		printf("CONT: %s\n", tree_node->cont.cmd);
	else if (tree_node->cont.pipe_c)
		printf("CONT: %c\n", tree_node->cont.pipe_c);
	else if (tree_node->cont.file)
		printf("CONT: %s\n", tree_node->cont.file);
	else if (tree_node->cont.limiter)
		printf("CONT: %s\n", tree_node->cont.limiter);
	else if (tree_node->cont.args)
	{
		printf("CONT: ");
		for (int i = 0; tree_node->cont.args[i]; i++)
			printf("%s ", tree_node->cont.args[i]);
		printf("\n");
	}
}

void    tree_apply_print(t_tree_node *root, int depth, char *side)
{
	if (root->right)
		tree_apply_print(root->right, depth + 1, "Right");
	print_tree(root, depth, side);
	if (root->left)
		tree_apply_print(root->left, depth + 1, "Left");
}
