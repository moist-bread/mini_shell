
#include "../../Inc/minishell.h"

/// @brief Main function that creates the AST_Tree 
/// @param tokens Node from the token list
/// @param cont The content
t_tree_node	*create_tree(t_token **tokens, t_minishell *ms)
{
	t_tree_node	*tree_node;

	tree_node = NULL;
	expand_token_list(tokens, ms);
	if (!tokens)
		return (NULL);
	assign_type_token(*tokens, true);
	// printf("\nafter expansion:\n");
	// print_tokens(*tokens);
	if (place_treenode(*tokens, &tree_node, false) == -1)
		return (NULL);
	// tree_apply_print(tree_node, 0, "Root");
	return (tree_node);
}

/// @brief Expands the content of the tokens
/// @param head The head of the tokens list
/// @param ms The minishell struct  
void	expand_token_list(t_token **head, t_minishell *ms)
{
	t_token	*curr;
	t_token	*next;

	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (curr->type != LIM && ft_strchr(curr->cont, '$'))
		{
			if (expander(curr, ms, head) == 1)
				return ;
		}
		else
		{
			if (process_token_quotes(curr) == 1)
				return ;
		}
		curr = next;
	}
}

/// @brief Assigns the content to the right place in the struct
/// @param token Node from the token list
/// @param cont The content
/// @return The content with the right stuff inside
t_node_cont	assign_tree_cont(t_token *token)
{
	t_node_cont	cont;

	ft_bzero(&cont, sizeof(t_node_cont));
	if (token && (token->type == CMD || token->type == BUILT_IN))
		cont.cmd = token->cont;
	else if (token && token->type == LIM)
	{
		cont.limiter = token->cont;
		cont.quote = token->quote;
	}
	else if (token && token->prev && (token->prev->type == RED_IN \
	|| token->prev->type == RED_OUT || token->prev->type == RED_APP) \
	&& token->type == ARG)
		cont.file = token->cont;
	else if (token && token->type == PIPE)
		cont.pipe_c = *token->cont;
	else if (token && token->type == ARG)
		cont.args = tree_alloc_args(token);
	return (cont);
}

/// @brief The functions that assigns the nodes when theres no pipe or left side
/// of the first pipe
/// @param tokens Node from the token list
/// @param new_tree_node New node of the AST_Tree
/// @param root The root of the AST_Tree
static int	if_not_pipe(t_token *tokens, t_tree_node *new_tree_node, \
t_tree_node **root)
{
	t_token	*cmd_token;

	cmd_token = tokens;
	while (cmd_token && cmd_token->type != PIPE && cmd_token->type != CMD \
	&& cmd_token->type != BUILT_IN)
		cmd_token = cmd_token->next;
	if (cmd_token && (cmd_token->type == CMD || cmd_token->type == BUILT_IN))
	{
		new_tree_node = newtreenode(assign_tree_cont(cmd_token));
		if (!new_tree_node)
			return (-1);
		new_tree_node->type = cmd_token->type;
	}
	else
	{
		new_tree_node = newtreenode(assign_tree_cont(NULL));
		if (!new_tree_node)
			return (-1);
		new_tree_node->type = CMD;
	}
	if (if_command(tokens, new_tree_node) == -1)
		return (-1);
	*root = new_tree_node;
	return (0);
}

/// @brief This functions puts the new tree_node in the right 
/// place in the AST_Tree
/// @param tokens Node from the token list
/// @param root The first node of the AST_Tree
/// @param cont The content of the nodes of the AST_Tree
int	place_treenode(t_token *tokens, t_tree_node **root, bool pipe)
{
	t_token		*pipe_token;
	t_tree_node	*new_tree_node;

	pipe_token = NULL;
	new_tree_node = NULL;
	if (pipe == false)
		pipe_token = iteri_till_pipe(tokens);
	if (pipe_token && pipe_token->type == PIPE)
	{
		new_tree_node = newtreenode(assign_tree_cont(pipe_token));
		if (!new_tree_node)
			return (-1);
		new_tree_node->type = pipe_token->type;
		if (pipe_token->next)
			place_treenode(pipe_token->next, &new_tree_node->right, false);
		place_treenode(tokens, &new_tree_node->left, true);
		*root = new_tree_node;
	}
	else
	{
		if (if_not_pipe(tokens, new_tree_node, root) == -1)
			return (-1);
	}
	return (0);
}
