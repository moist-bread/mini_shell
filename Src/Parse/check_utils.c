
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
	{
		printf("Error Quote\n");
		exit (1);
	}
}

/// @brief If is Operator
/// @param token Node of the token list
/// @return True if is Operator, False if is not 
bool	is_token(t_token *token)
{
	if (token->type == PIPE || token->type == REDIR_HERE_DOC || token->type == REDIR_IN \
	|| token->type == REDIR_OUT || token->type == REDIR_OUT_APPEND)
		return (true);
	return (false);
}

/// @brief Merge
/// @param input 
/// @return 
char	*merge_adjacent_segments(char *input)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = ft_calloc(1, ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				result[j++] = input[i++];
			if (input[i] == quote)
				i++;
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

/// @brief Puts space between two Pipes
/// @param j Increment
/// @param i Increment
/// @param dest The updated input 
void	check_double_pipe(int *j, int *i, char *dest)
{
	dest[(*j)++] = '|';
	dest[(*j)++] = ' ';
	dest[(*j)++] = '|';
	*i += 2;
}