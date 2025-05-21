

#include "../../Inc/minishell.h"

/// @brief The master function for the checks in the list of tokens 
/// @param token Node of a list 
void	master_check(t_token **token)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	while (temp)
	{
		if (temp->prev == NULL && temp->type == PIPE)
			ft_error_check(token);
		else if (temp->next && temp->type == PIPE && temp->next->type == PIPE)
			ft_error_check(token);
		else if (temp->next && temp->type != PIPE && is_token(temp) == true \
		&& is_token(temp->next) == true)
			ft_error_check(token);
		else if (is_token(temp) == true && temp->next == NULL)
			ft_error_check(token);
		if (!*token)
			return;
		temp = temp->next;
	}
}
