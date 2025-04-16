

#include "../../Inc/minishell.h"

void	master_check(t_token *token)
{
	t_token	*temp;

	if (!token)
		return (NULL);
	temp = token;
	while (temp)
	{
		checks_here_doc(temp);
	}
}

void	checks_here_doc(t_token	*token)
{
	t_token	*temp;

	if (!token)
		return (NULL);
	temp = token;
	while (temp)
	{
		if (temp->prev->type == REDIR_HERE_DOC && temp->type != ARG)
			ft_error_check(token);
	}
}