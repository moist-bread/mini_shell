
#include "../../Inc/minishell.h"

/// @brief Puts the node in the end of the list
/// @param tklst List of tokens 
/// @param newtk The new token
void	tokenadd_back(t_token **tklst, t_token *newtk)
{
	t_token *temptk;

	if (!*tklst)
	{
		*tklst = newtk;
		newtk->next = NULL;
		newtk->prev = NULL;
		return ;
	}
	temptk = *tklst;
	while (temptk->next)
		temptk = temptk->next;
	temptk->next = newtk;
	newtk->next = NULL;
	newtk->prev = temptk;
}

/// @brief Puts the node in the beggining of the list
/// @param tklst List of tokens 
/// @param newtk New token
void	tokenadd_front(t_token **tklst, t_token *newtk)
{
	if (!newtk)
		return ;
	newtk->next = *tklst;
	newtk->prev = NULL;
	if (*tklst)
		(*tklst)->prev = newtk;
	*tklst = newtk;

}

/// @brief Creates a node named token
/// @param cont Content of the token 
/// @return The new token
t_token	*newtoken(char *cont)
{
	t_token	*newtk;

	newtk = ft_calloc(1, sizeof(t_token));
	if (!newtk)
		return (NULL);
	newtk->cont = cont;
	newtk->next = NULL;
	newtk->prev = NULL;
	return (newtk);
}

/// @brief Prints the node in order, there type and content
/// @param tokens The token of the list 
void	print_tokens(t_token *tokens)
{
	t_token	*curr;
	int		i;

	if (!tokens)
		return ;
	curr = tokens;
	i = 0;
	while (curr)
	{
		printf("Token[%d]: %s", i, curr->cont);
		printf("\t");
		assign_name(curr->type);
		printf("\t");
		printf("ID: %u\n", curr->type);
		curr = curr->next;
		i++;
	}
}

