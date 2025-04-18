

#include "../../Inc/minishell.h"

// void	print_tree(t_tree_node *root)
// {
// 	if(!root)
// 		return ;

// }

// void	create_tree(t_token *tokens, t_node_cont *cont)
// {
// 	t_tree_node	*tree_node;
	
// 	tree_node = NULL;
// 	tree_cont_init(cont);
// 	place_tree_node(tokens, &tree_node, cont);

// }

// t_node_cont	*assign_tree_cont(t_token *token, t_node_cont *cont)
// {
// 	int	i;

// 	i = 0;
// 	if (token && token->type == CMD)
// 		cont->cmd = token->cont;
// 	else if (token && token->type == LIM)
// 		cont->limiter = token->cont;
// 	else if (token && token->prev && (token->prev->type == REDIR_IN \
// 	|| token->prev->type == REDIR_OUT || token->prev->type == REDIR_OUT_APPEND))
// 		cont->file = token->cont;
// 	// else if (token && token->type == PIPE)
// 	else if (token && token->type == ARG)
// 		cont->args = tree_alloc_args(token);
// 	return (cont);
// }

// void	place_treenode(t_token *tokens, t_tree_node **root, t_node_cont *cont)
// {
// 	int			i;
// 	// t_token		*temp;
// 	t_tree_node	*new_tree_node;

// 	i = 0;
// 	iteri_till_pipe(tokens);
// 	assign_tree_cont(tokens, cont);
// 	// temp = tokens;
// 	// while(temp)
// 	// {
// 	// 	new_tree_node = newtreenode();
// 	// }
// }
