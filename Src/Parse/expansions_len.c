
#include "../../Inc/minishell.h"

/// @brief Retrieves the lenght of the quoted string
/// @param input The string passed
/// @param env The enviorment 
/// @param i Indexes
/// @return The lenght
size_t	len_double_quotes(char *input, char **env, int *i, int exit_status)
{
	size_t len;

	len = 1;
	(*i)++;
	while (input[(*i)] && input[*i] != '\"')
	{
		if (input[*i] == '$' && (isalpha(input[*i + 1]) || input[*i + 1] == '_'))
		{
			len += len_expansion(input + *i, env);
			while (input[++(*i)] == '_' || ft_isalnum(input[*i]))
				;
		}
		else if (input[*i] == '$' && ft_isdigit(input[*i + 1]))
			*i += 2;
		else if (input[*i] == '$' && input[*i + 1] == '?')
			len_exit_status(ft_itoa(exit_status), &len, i);
		else
		{
			(*i)++;
			len++;
		}
	}
	if (input[(*i)++] == '\"')
        len++;
	printf("len_double: %zu\n", len);
	return (len);
}

/// @brief Retrieves the lenght of the single quoted string
/// @param input The string passed
/// @param i Indexes
/// @return The length
size_t	len_single_quote(char *input, int *i)
{
	size_t len;

	len = 1;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	if (input[*i] == '\'')
	{
        len++;
        (*i)++;
    }
	return (len);
}

/// @brief Retrieves the lenght of the unquoted string
/// @param input The string passed
/// @param env The enviorment 
/// @param i Indexes
/// @return The length
size_t	len_unquoted(char *input, char **env, int *i, int exit_status)
{
	size_t	len;

	len = 0;
	while (input[*i] && input[*i] != '\"' && input[*i] != '\'')
	{
		if (input[*i] == '$' && (isalpha(input[*i + 1]) || input[*i + 1] == '_'))
		{
			len += len_expansion(input + *i, env);
			while (input[++(*i)] == '_' || ft_isalnum(input[*i]))
				;
		}
		else if (input[*i] == '$' && ft_isdigit(input[*i + 1]))
			*i += 2;
		else if (input[*i] == '$' && input[*i + 1] == '?')
			len_exit_status(ft_itoa(exit_status), &len, i);
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

/// @brief Main function that retrieves the length
/// @param input The string passed
/// @param env The enviorment 
/// @return The length
size_t	the_length(char *input, t_minishell ms)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			len += len_double_quotes(input, ms.env, &i, ms.exit_status);
		else if (input[i] == '\'')
			len += len_single_quote(input, &i);
		else
			len += len_unquoted(input, ms.env, &i, ms.exit_status);
	}
	return (len);
}

/// @brief Gets the lenght of the expanded variable on the enviorment
/// @param input The string passed
/// @param env The enviorment 
/// @return the length
size_t	len_expansion(char *input, char **env)
{
	char	*value;
	char	*search;
	size_t	len;

	len = 0;
	search = get_search(input);
	value = get_env(search, env);
	if (!value)
		return (free(search), 0);
	if (value)
		len = ft_strlen(value);
	free(search);
	return (len);
}