
#include "../../Inc/minishell.h"

void	tokenadd_back(t_token **tklst, t_token *newtk)
{
	t_token *temptk;

	if (!*tklst)
	{
		newtk->next = NULL;
		return ;
	}
	temptk = *tklst;
	while (temptk)
		temptk = temptk->next;
	temptk->next = newtk;
}

void	tokenadd_front(t_token **tklst, t_token *newtk)
{
	if (newtk)
	{
		newtk->next = *tklst;
		*tklst = newtk;
	}
}

