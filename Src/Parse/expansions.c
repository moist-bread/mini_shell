
#include "../../Inc/minishell.h"

/// @brief Processes the expansion of the string passed
/// @param input The string passed
/// @param env The enviorment
/// @param is_quote Flag to know if the expansion is between quotes
/// @return The expanded string
char	*process_quote_expansions(char *input, t_minishell ms, int *is_quote)
{
	char	*result;
	char	*checked;
	long	result_len;

	if (!input)
		return (ft_strdup(""));
	checked = check_expansion(input);
	if (!checked)
		return (NULL);
	result_len = the_length(checked, ms);
	if (result_len == -1)
		return (free(checked), NULL);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (perror("malloc9"), free(checked), NULL);
	if (the_expansion(checked, ms, is_quote, result) == 1)
		return (free(checked), free(result), NULL);
	free(checked);
	return (result);
}

/// @brief Does the espansion
/// @param input The string passed
/// @param env The enviorment
/// @param result The string that will receive the expansion
/// @param is_quote Flag to know if the expansion is between quotes
int	the_expansion(char *input, t_minishell ms, int *is_quote, char *result)
{
	int	i[2];

	ft_bzero(i, sizeof(i));
	while (input[i[0]])
	{
		if (input[i[0]] == '\"')
		{
			if (expand_double_quotes(input, result, i, ms) == 1)
				return (1);
		}
		else if (input[i[0]] == '\'')
			expand_single_quotes(input, result, i);
		else
		{
			if (expand_unquotes(input, result, i, ms) == 1)
				return (1);
			*is_quote = 0;
		}
	}
	return (0);
}

/// @brief Expands if the expansion is between quotes
/// @param s The string passed
/// @param env The enviorment
/// @param result The string that will receive the expansion
/// @param i Indexes
int	expand_double_quotes(char *s, char *result, int *i, t_minishell ms)
{
	result[i[1]++] = s[i[0]++];
	while (s[i[0]] && s[i[0]] != '\"')
	{
		if (handle_variable_expansion(s, i, result, ms.env))
			return (1);
		else if (s[i[0]] == '$' && ft_isdigit(s[i[0] + 1]))
			i[0] += 2;
		else if (s[i[0]] == '$' && s[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = s[i[0]++];
	}
	result[i[1]] = s[i[0]];
	return (0);
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
int	expand_unquotes(char *s, char *result, int *i, t_minishell ms)
{
	char	*exp;
	bool	flag;

	flag = false;
	while (s[i[0]] && s[i[0]] != '\"' && s[i[0]] != '\'')
	{
		if (s[i[0]] == '$' && (ft_isalpha(s[i[0] + 1]) || s[i[0] + 1] == '_'))
		{
			exp = expansion(s + i[0], ms.env, &flag);
			if (flag)
				return (1);
			if (exp)
				write_and_advance(result, &i[1], exp);
			while (s[++i[0]] && (s[i[0]] == '_' || ft_isalnum(s[i[0]])))
				;
		}
		else if (s[i[0]] == '$' && ft_isdigit(s[i[0] + 1]))
			i[0] += 2;
		else if (s[i[0]] == '$' && s[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = s[i[0]++];
	}
	return (0);
}
