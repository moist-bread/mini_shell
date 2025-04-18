
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
	newtk->cont = ft_strdup(cont);
	newtk->next = NULL;
	newtk->prev = NULL;
	newtk->type = 1;
	return (newtk);
}

/// @brief This functions clears the token list
/// @param token Head node of the list
void	clear_token_lst(t_token	*token)
{
	t_token *current;
	t_token *next;

	if (!token)
		return;
	current = token;
	while (current)
	{
		next = current->next;
		if (current->cont)
			free(current->cont);
		free(current);
		current = next;
	}
}

/// @brief Goes through the token until it finds a PIPE
/// @param token Node of the list 
/// @return The token that have the PIPE or The start 
///of the list if doesn't find something
t_token	*iteri_till_pipe(t_token *token)
{
	t_token *start;

	start = token;
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (start);
}
