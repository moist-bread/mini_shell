

#include "../../Inc/minishell.h"

void	master_check(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (temp)
	{
		if (temp->prev == NULL && temp->type == PIPE)
			ft_error_check(token);
		if (temp->next && is_token(temp) == true && is_token(temp->next) == true)
			ft_error_check(token);
		if (is_token(temp) == true && temp->next == NULL)
			ft_error_check(token);
		temp = temp->next;
	}
}

// void	checks_here_doc(t_token	*token)
// {
// 	t_token	*temp;

// 	if (!token)
// 		return ;
// 	temp = toke
// 		if (temp->prev->type == REDIR_HERE_DOC && temp->type != ARG)
// 			ft_error_check(token);
// }