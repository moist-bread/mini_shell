

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

/// @brief Basic error function
/// @param token Node of the token list
void	ft_error_check(t_token *token)
{
	fake_clear_token_lst(token);
	printf("Invalid Syntax\n");
	exit(1);
}

void	error_quote_check(char *s)
{
	printf("%s\n", s);
	exit (1);
}