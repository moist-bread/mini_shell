
#include "../../Inc/minishell.h"

char	**tree_alloc_args(t_token *token, t_node_cont *cont)
{
	t_token *temp;
	t_token *content;
	char	**args;
	int		i;

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

void	left_or_right(t_tree_node *tree_node)
{
	if (!tree_node)
		return ;
		
}

void	tree_node_addleft(t_tree_node *tree_node)
{

}

void	tree_node_addright(t_tree_node *tree_node)
{
	
}