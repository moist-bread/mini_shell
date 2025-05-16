
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
	newtk->type = ARG;
	return (newtk);
}

/// @brief This functions clears the token list
/// @param token Head node of the list
void	fake_clear_token_lst(t_token	*token)
{
	t_token *current;
	t_token *next;

	if (!token)
		return;
	current = token;
	while (current)
	{
		next = current->next;
		if (current->type == PIPE || (current->type >= REDIR_IN
			&& current->type <= REDIR_OUT_APPEND))
			free(current->cont);
		free(current);
		current = next;
	}
}

void	replace_expanded_token(t_token **head, t_token *curr, char **expanded)
{
	t_token	*temp;
	t_token *newtk;
	t_token	*first_new;
	int		i;

	first_new = NULL;
	i = 0;
	while (expanded[i])
	{
		newtk = newtoken(expanded[i]);
		tokenadd_back(&first_new, newtk);
		i++;
	}
	temp = first_new;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = curr->next;
	if (curr && curr->prev)
		curr->prev->next = first_new;
	else
		*head = first_new;
}
