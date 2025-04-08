
#include "../../Inc/minishell.h"

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
	newtk->prev = temptk;
	newtk->next = NULL;
}

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

t_token	*newtoken(char *cont, t_node_type type)
{
	t_token	*newtk;

	newtk = malloc(sizeof(t_token));
	if (!newtk)
		return (NULL);
	newtk->cont = cont;
	newtk->type = type;
	newtk->next = NULL;
	newtk->prev = NULL;
	return (newtk);
}

