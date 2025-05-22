

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
		if (current->type == PIPE || (current->type >= REDIR_IN
			&& current->type <= REDIR_OUT_APPEND))
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

/// @brief Basic error function
/// @param token Node of the token list
void	ft_error_check(t_token **token)
{
	printf("syntax error near unexpected token\n");
	syntax_clear(*token);
	*token = NULL;
}

void	len_exit_status(char *exit_status, size_t *len, int *i)
{
	*len += ft_strlen(exit_status);
	*i += 2;
	free(exit_status);
}