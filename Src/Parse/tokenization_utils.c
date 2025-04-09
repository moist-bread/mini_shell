
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
	newtk->next = NULL;
	newtk->prev = temptk;
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

t_token	*newtoken(char *cont)
{
	t_token	*newtk;

	newtk = malloc(sizeof(t_token));
	if (!newtk)
		return (NULL);
	newtk->cont = cont;
	newtk->next = NULL;
	newtk->prev = NULL;
	return (newtk);
}

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

