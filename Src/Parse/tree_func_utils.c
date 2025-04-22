
#include "../../Inc/minishell.h"

/// @brief Allocates memory if the content is ARG 
/// @param token The Node from the token list
/// @param cont The content
/// @return The char** that is the consecutive arguments
char	**tree_alloc_args(t_token *token, t_node_cont *cont)
{
	t_token *temp;
	t_token *content;
	char	**args;
	int		i;

	// printf("Entered Tree Alloc Args\n");
	temp = token;
	content = token;
	i = 0;
	while (content && content->type == PIPE)
	{
		i++;
		content = content->next;
	}
	args = ft_calloc(sizeof(char *), i + 1);
	if (!cont->args)
		return (NULL);
	i = 0;
	while (temp->type == ARG)
	{
		args[i++] = temp->cont;
		temp = temp->next; 
	}
	return (args);
}

/// @brief The fuction will assingn the content if the Node is a CMD node
/// @param tokens The Node from the token list
/// @param cmd_node The Node from the Binary Tree
void	if_command(t_token *tokens, t_tree_node *cmd_node)
{
	t_token		*temp;
	t_tree_node	*redir_node;
	t_tree_node	*arg_node;

	temp = tokens;
	redir_node = NULL;
	arg_node = NULL;
	// printf("Entered If Command\n");
	if (temp && (temp->type == REDIR_HERE_DOC || temp->type == REDIR_IN || temp->type == REDIR_OUT \
		|| temp->type == REDIR_OUT_APPEND))
	{
		redir_node = newtreenode(assign_tree_cont(tokens));
		cmd_node->left = redir_node;
		temp = temp->next;
	}
	else if (temp && temp->type == ARG)
	{
		arg_node = newtreenode(assign_tree_cont(tokens));
		cmd_node->right = arg_node;
		temp = temp->next;
	}
}

/// @brief Goes through the token until it finds a PIPE
/// @param token Node of the list 
/// @return The token that have the PIPE or The start 
///of the list if doesn't find something
t_token	*iteri_till_pipe(t_token *token)
{
	t_token *start;

	// printf("Entered Iteri PIPE\n");
	start = token;
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
