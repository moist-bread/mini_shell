
#include "../../Inc/minishell.h"

/// @brief Main function that creates the AST_Tree 
/// @param tokens Node from the token list
/// @param cont The content
t_tree_node	*create_tree(t_token **tokens, t_minishell *ms)
{
	t_tree_node	*tree_node;
	
	tree_node = NULL;
	expand_token_list(tokens, ms);
	assign_type_token(*tokens, true);
	printf("after expansion:\n");
	print_tokens(*tokens);
	place_treenode(*tokens, &tree_node, false);
	tree_apply_print(tree_node, 0, "Root");
	printf("\n");
	return (tree_node);
}

/// @brief Expands the content of the tokens
/// @param head The head of the tokens list
/// @param ms The minishell struct  
void	expand_token_list(t_token **head, t_minishell *ms)
{
	t_token	*curr;
	char	**expanded;
	char	*new_cont;

	curr = *head;
	while (curr)
	{
		if (curr->type != LIM && ft_strchr(curr->cont, '$'))
		{
			expanded = input_expander(curr->cont, *ms);
			curr = replace_expanded_token(head, curr, expanded);
			free_split(expanded);
			continue ;
		}
		else
		{
			if (curr->type == LIM && (ft_strchr(curr->cont, '\"') 
			|| ft_strchr(curr->cont, '\'')))
				ms->quote = true;
			new_cont = quote_remover(curr->cont);
			free(curr->cont);
       		curr->cont = new_cont;
			curr = curr->next;
		}
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
		cont.limiter = token->cont;
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
static void	if_not_pipe(t_token *tokens, t_tree_node *new_tree_node, t_tree_node **root)
{
	t_token *cmd_token;
	
	cmd_token = tokens;
	while (cmd_token && cmd_token->type != PIPE && cmd_token->type != CMD && cmd_token->type != BUILT_IN)
		cmd_token = cmd_token->next;
	if (cmd_token && (cmd_token->type == CMD || cmd_token->type == BUILT_IN))
	{
		new_tree_node = newtreenode(assign_tree_cont(cmd_token));
		new_tree_node->type = cmd_token->type;
	}
	else
	{
		new_tree_node = newtreenode(assign_tree_cont(NULL));
		new_tree_node->type = CMD;
	}
	if_command(tokens, new_tree_node);
	*root = new_tree_node;
}

/// @brief This functions puts the new tree_node in the right place in the AST_Tree
/// @param tokens Node from the token list
/// @param root The first node of the AST_Tree
/// @param cont The content of the nodes of the AST_Tree
void	place_treenode(t_token *tokens, t_tree_node **root, bool pipe)
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
		new_tree_node->type = pipe_token->type;
		if (pipe_token->next)
			place_treenode(pipe_token->next, &new_tree_node->right, false);
		place_treenode(tokens, &new_tree_node->left, true);
		*root = new_tree_node;
	}
	else
		if_not_pipe(tokens, new_tree_node, root);
}
