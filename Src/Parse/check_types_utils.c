
#include "../../Inc/minishell.h"

/// @brief Checks if the quotes are impar and gives an error if they are
/// @param input String
bool	check_quotes(char *input)
{
	int		i;
	int 	quote;
	char	is_quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			is_quote = input[i++];
			quote++;
			while (input[i] && input[i] != is_quote)
				i++;
			if (input[i] && input[i++] == is_quote)
				quote++;
		}
		else
			i++;
	}
	if (quote % 2 != 0)
		return (printf("Invalid Syntax\n"), false);
	return (true);
}

/// @brief If is Operator
/// @param token Node of the token list
/// @return True if is Operator, False if is not 
bool	is_token(t_token *token)
{
	if (token->type == PIPE || token->type == RED_HD \
	|| token->type == RED_IN \
	|| token->type == RED_OUT || token->type == RED_APP)
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
			quote = input[i];
			result[j++] = input[i++];
			while (input[i] && input[i] != quote)
				result[j++] = input[i++];
			if (input[i] == quote)
				result[j++] = input[i++];
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

void	is_limtiter_or_arg(t_token **temp)
{
	if ((*temp)->cont == NULL)
		(*temp)->type = ARG;
	else if ((*temp)->type == RED_HD && (*temp)->next)
	{
		*temp = (*temp)->next;
		(*temp)->type = LIM;
		
	}
	else if (is_token(*temp) && (*temp)->next)
	{
		*temp = (*temp)->next;
		(*temp)->type = ARG;
		assigns_types(*temp, false);
	}
}
