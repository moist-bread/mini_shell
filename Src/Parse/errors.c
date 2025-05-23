

#include "../../Inc/minishell.h"


void	fake_clear_token_lst(t_token *token)
{
	t_token *current;
	t_token *next;

	if (!token)
		return;
	current = token;
	while (current)
	{
		next = current->next;
		if (current->type == PIPE || (current->type >= RED_IN
			&& current->type <= RED_APP))
			free(current->cont);
		free(current);
		current = next;
	}
}

void	syntax_clear(t_token *token)
{
	t_token *current;
	t_token *next;

	if (!token)
		return;
	current = token;
	while (current)
	{
		next = current->next;
		free(current->cont);
		free(current);
		current = next;
	}
}

void	len_exit_status(char *exit_status, size_t *len, int *i)
{
	*len += ft_strlen(exit_status);
	*i += 2;
	free(exit_status);
}