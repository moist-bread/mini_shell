
#include "../../Inc/minishell.h"

/// @brief Allocates memory if the content is ARG 
/// @param token The Node from the token list
/// @param cont The content
/// @return The char** that is the consecutive arguments
char	**tree_alloc_args(t_token *token)
{
	t_token *temp;
	t_token *content;
	char	**args;
	int		i;

	temp = token;
	content = token;
	i = 0;
	while (content && content->type == ARG && content->type != PIPE)
	{
		i++;
		content = content->next;
	}
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (temp && temp->type == ARG && temp->type != PIPE)
	{
		args[i] = temp->cont;
		i++;
		temp = temp->next;
	}
	return (args);
}

/// @brief The fuction will assingn the content if the Node is a CMD node
/// @param tokens The Node from the token list
/// @param cmd_node The Node from the AST_Tree
void	if_command(t_token *tokens, t_tree_node *cmd_node)
{
	t_token		*temp;

	temp = tokens->next;
	while (temp && temp->type != PIPE)
	{
		if (temp && (temp->type <= REDIR_IN && temp->type >= REDIR_OUT_APPEND))
		{
			cmd_node->left = newtreenode(assign_tree_cont(temp->next));
			printf("Creating REDIR node for: %s\n", cmd_node->right->cont.file);
			temp = temp->next;
		}
		else if (temp && temp->type == ARG)
		{
			cmd_node->right = newtreenode(assign_tree_cont(temp));
			printf("Creating ARG node for: %s\n", cmd_node->right->cont.args[0]);
		}
		temp = temp->next;
	}
}

/// @brief Goes through the token until it finds a PIPE
/// @param token Node of the list 
/// @return The token that have the PIPE or The start 
///of the list if doesn't find something
t_token	*iteri_till_pipe(t_token *token)
{
	// t_token *start;

	// printf("Entered Iteri PIPE\n");
	// start = token;
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/// @brief Function that prints the AST_Tree
/// @param tree_node The First Node of the Tree
void	print_tree(t_tree_node *tree_node, int depth, char *side)
{
	int	i;

	// printf("Entered Print Tree\n");
	i = 1;
	if(!tree_node)
		return ;
	while (i++ <= depth)
		printf("\t");
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

	i = 1;
	while (i++ <= depth)
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
