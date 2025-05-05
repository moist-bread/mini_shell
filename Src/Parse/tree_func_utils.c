
#include "../../Inc/minishell.h"

/// @brief Counts the number of arguments that the CMD contain
/// @param token The node that has the arguments
/// @param temp Temporary node 
/// @return Returns the number of arguments
static int	tree_arg_len(t_token *token, t_token *temp)
{
	t_token *content;
	int	i;

	i = 0;
	content = token;
	while (content && content->type != PIPE)
	{
		if (temp->type == ARG)
		{
			if (temp->prev && temp->type == ARG \
			&& temp->prev->type >= REDIR_IN && temp->prev->type <= REDIR_OUT_APPEND)
				i--;
			i++;
		}
		content = content->next;
	}
	return (i);
}

/// @brief Allocates memory if the content is ARG 
/// @param token The Node from the token list
/// @param cont The content
/// @return The char** that is the consecutive arguments
char	**tree_alloc_args(t_token *token)
{
	t_token *temp;
	char	**args;
	int		i;

	// printf("TREE ALLOC\n");
	temp = token;
	i = tree_arg_len(token, temp);
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (temp && temp->type != PIPE)
	{
			if (temp->prev && temp->type == ARG \
			&& temp->prev->type >= REDIR_IN && temp->prev->type <= REDIR_OUT_APPEND)
				temp = temp->next;
		 	if (temp->type == ARG)
				args[i++] = temp->cont;
		if (temp->type != PIPE)
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
	bool		st_arg;

	st_arg = false;
	temp = tokens->next;
	while (temp && temp->type != PIPE)
	{
		if (temp && (temp->type >= REDIR_IN && temp->type <= REDIR_OUT_APPEND))
		{
			cmd_node->left = newtreenode(assign_tree_cont(temp->next));
			cmd_node->left->type = temp->type;
			printf("Creating REDIR node for: %s\n", cmd_node->left->cont.file);
			temp = temp->next;
			cmd_node = cmd_node->left;
		}
		else if (temp && temp->type == ARG && st_arg == false)
		{
			cmd_node->right = newtreenode(assign_tree_cont(temp));
			cmd_node->right->type = ARG;
			st_arg = true; 
			printf("Creating ARG node for: ");
			for (int i = 0; cmd_node->right->cont.args[i]; i++)
				printf("%s ",cmd_node->right->cont.args[i]);
			printf("\n");
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
		assign_name(tree_node->type);
	else if (tree_node->cont.file)
		assign_name(tree_node->type);
	else if (tree_node->cont.limiter)
		assign_name(tree_node->type);
	else if (tree_node->cont.args)
		assign_name(tree_node->type);
	else
		assign_name(tree_node->type);
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
