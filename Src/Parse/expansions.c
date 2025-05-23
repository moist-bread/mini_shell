
#include "../../Inc/minishell.h"

/// @brief Processes the expansion of the string passed
/// @param input The string passed
/// @param env The enviorment
/// @param is_quote Flag to know if the expansion is between quotes
/// @return The expanded string
char	*process_quote_expansions(char *input, t_minishell ms, int *is_quote)
{	
	char	*result;
	size_t	result_len;

	if (!input)
		return (ft_strdup(""));
	result_len = the_length(input, ms);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (NULL);
	the_expansion(input, ms, is_quote, result);
	return (result);
}

/// @brief Does the espansion
/// @param input The string passed
/// @param env The enviorment
/// @param result The string that will receive the expansion
/// @param is_quote Flag to know if the expansion is between quotes
void	the_expansion(char *input, t_minishell ms, int *is_quote, char *result)
{
	int		i[2] = {0, 0};

	while (input[i[0]])
	{
		if (input[i[0]] == '\"')
			expand_double_quotes(input, result, i, ms);
		else if (input[i[0]] == '\'')
			expand_single_quotes(input, result, i);
		else
		{
			expand_unquotes(input, result, i, ms);
			*is_quote = 0; 
		}
	}
}

/// @brief Expands if the expansion is between quotes
/// @param input The string passed
/// @param env The enviorment
/// @param result The string that will receive the expansion
/// @param i Indexes
void	expand_double_quotes(char *input, char *result, int *i, t_minishell ms)
{
	char	*exp;

	result[i[1]++] = input[i[0]++];
	while (input[i[0]] && input[i[0]] != '\"')
	{
		if (input[i[0]] == '$' && (ft_isalpha(input[i[0] + 1]) || input[i[0] + 1] == '_'))
		{
			exp = expansion(input + i[0], ms.env);
			if (exp)
			{
				ft_memcpy(result + i[1], exp, ft_strlen(exp));
				i[1] += ft_strlen(exp);
				free(exp);
			}
			while (input[++i[0]] && (input[i[0]] == '_' || ft_isalnum(input[i[0]])))
				;
		}
		else if (input[i[0]] == '$' && ft_isdigit(input[i[0] + 1]))
			i[0] += 2;
		else if (input[i[0]] == '$' && input[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = input[i[0]++];
	}
	result[i[1]++] = input[i[0]++];
}

/// @brief xpands if the expansion is between single quotes
/// @param input The string passed
/// @param result The string that will receive the expansion
/// @param i Indexes
void	expand_single_quotes(char *input, char *result, int *i)
{
	result[i[1]++] = input[i[0]++];
	while (input[i[0]] && input[i[0]] != '\'')
		result[i[1]++] = input[i[0]++];
	if (input[i[0]] == '\'')
		result[i[1]++] = input[i[0]++];
}

/// @brief Expands if the expansion is not between quotes
/// @param input The string passed
/// @param env The enviorment
/// @param result The string that will receive the expansion
/// @param i Indexes
void	expand_unquotes(char *input, char *result, int *i, t_minishell ms)
{
	char	*exp;

	while (input[i[0]] && input[i[0]] != '\"' && input[i[0]] != '\'')
	{
		if (input[i[0]] == '$' && (ft_isalpha(input[i[0] + 1]) || input[i[0] + 1] == '_'))
		{
			exp = expansion(input + i[0], ms.env);
			if (exp)
			{
				ft_memcpy(result + i[1], exp, ft_strlen(exp));
				i[1] += ft_strlen(exp);
				free(exp);
			}
			while (input[++i[0]] && (input[i[0]] == '_' || ft_isalnum(input[i[0]])))
				;
		}
		else if (input[i[0]] == '$' && ft_isdigit(input[i[0] + 1]))
			i[0] += 2;
		else if (input[i[0]] == '$' && input[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = input[i[0]++];
	}
}
