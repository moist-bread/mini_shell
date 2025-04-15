
#include "../../Inc/minishell.h"

/// @brief Checks if the quotes are impar
/// @param input String
void	check_quotes(char *input)
{
	int	i;
	int quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		exit (1);
}

bool	is_token(t_token *token)
{
	if (token->type == PIPE || token->type == REDIR_HERE_DOC || token->type == REDIR_IN \
	|| token->type == REDIR_OUT || token->type == REDIR_OUT_APPEND)
		return (true);
	return (false);
}