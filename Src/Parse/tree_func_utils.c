/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:54:47 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 18:55:10 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Counts the number of arguments that the CMD contain
/// @param token The node that has the arguments
/// @param temp Temporary node
/// @return Returns the number of arguments
static int	tree_arg_len(t_token *token, t_token *temp)
{
	t_token	*content;
	int		i;

	i = 0;
	content = token;
	while (content && content->type != PIPE)
	{
		if (temp->type == ARG)
		{
			if (temp->prev && temp->type == ARG && temp->prev->type >= RED_IN
				&& temp->prev->type <= RED_APP)
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
	t_token	*temp;
	char	**args;
	int		i;

	temp = token;
	i = tree_arg_len(token, temp);
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (perror("malloc12"), NULL);
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->prev && temp->type == ARG && temp->prev->type >= RED_IN \
			&& temp->prev->type <= RED_APP)
			temp = temp->next;
		if (temp && temp->type == ARG && temp->cont != NULL)
			args[i++] = temp->cont;
		if (temp && temp->type != PIPE)
			temp = temp->next;
	}
	return (args);
}

/// @brief It creates the node of the AST_Tree if is any kind of Redir
/// @param temp Temporary Node
/// @param cmd_node Cmd node of the AST_Tree
/// @param last_redir The last created Node of the AST_Tree that is type Redir
static int	if_redir(t_token **temp, t_tree_node *cmd_node,
		t_tree_node **last_redir)
{
	t_tree_node	*redir_node;

	if (!(*temp) || !(*temp)->next)
		return (-1);
	redir_node = newtreenode(assign_tree_cont((*temp)->next));
	if (!redir_node)
		return (-1);
	redir_node->type = (*temp)->type;
	if (!cmd_node->left)
		cmd_node->left = redir_node;
	else if (*last_redir)
		(*last_redir)->left = redir_node;
	*last_redir = redir_node;
	*temp = (*temp)->next;
	return (0);
}

/// @brief The fuction will assingn the content if the Node is a CMD node
/// @param tokens The Node from the token list
/// @param cmd_node The Node from the AST_Tree
int	if_command(t_token *tokens, t_tree_node *cmd_node)
{
	t_token		*temp;
	t_tree_node	*last_redir;
	bool		ag;

	ag = false;
	last_redir = NULL;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp && (temp->type >= RED_IN && temp->type <= RED_APP))
		{
			if (if_redir(&temp, cmd_node, &last_redir) == -1)
				return (-1);
		}
		else if (temp && temp->type == ARG && ag == false && temp->cont != NULL)
		{
			cmd_node->right = newtreenode(assign_tree_cont(temp));
			if (!cmd_node->right)
				return (-1);
			cmd_node->right->type = ARG;
			ag = true;
		}
		temp = temp->next;
	}
	return (0);
}

/// @brief Goes through the token until it finds a PIPE
/// @param token Node of the list
/// @return The token that have the PIPE or The start
/// of the list if doesn't find something
t_token	*iteri_till_pipe(t_token *token)
{
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
