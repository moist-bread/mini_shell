
#include "../../Inc/minishell.h"

/// @brief Retrieves the lenght of the quoted string
/// @param input The string passed
/// @param env The enviorment 
/// @param i Indexes
/// @return The lenght
long	len_double_quotes(char *s, char **env, int *i, int exit_status)
{
	long	len;

	len = 1;
	(*i)++;
	while (s[(*i)] && s[*i] != '\"')
	{
		if (s[*i] == '$' && (ft_isalpha(s[*i + 1]) || s[*i + 1] == '_'))
		{
			len += len_expansion(s + *i, env);
			if (len == 0)
				return (-1);
			while (s[++(*i)] == '_' || ft_isalnum(s[*i]))
				;
		}
		else if (s[*i] == '$' && ft_isdigit(s[*i + 1]))
			*i += 2;
		else if (s[*i] == '$' && s[*i + 1] == '?')
			len_exit_status(ft_itoa(exit_status), &len, i);
		else
		{
			(*i)++;
			len++;
		}
	}
	return ((*i)++, len + 1);
}

/// @brief Retrieves the lenght of the single quoted string
/// @param input The string passed
/// @param i Indexes
/// @return The length
long	len_single_quote(char *input, int *i)
{
	long	len;

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
long	len_unquoted(char *s, char **env, int *i, int exit_status)
{
	long	len;

	len = 0;
	while (s[*i] && s[*i] != '\"' && s[*i] != '\'')
	{
		if (s[*i] == '$' && (ft_isalpha(s[*i + 1]) || s[*i + 1] == '_'))
		{
			len += len_expansion(s + *i, env);
			if (len == -1)
				return (-1);
			while (s[++(*i)] == '_' || ft_isalnum(s[*i]))
				;
		}
		else if (s[*i] == '$' && ft_isdigit(s[*i + 1]))
			*i += 2;
		else if (s[*i] == '$' && s[*i + 1] == '?')
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
long	the_length(char *input, t_minishell ms)
{
	long	len;
	int		i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			len += len_double_quotes(input, ms.env, &i, ms.exit_status);
			if (len == -1)
				return (-1);
		}
		else if (input[i] == '\'')
			len += len_single_quote(input, &i);
		else
		{
			len += len_unquoted(input, ms.env, &i, ms.exit_status);
			if (len == -1)
				return (-1);
		}
	}
	
	return (len);
}

/// @brief Gets the lenght of the expanded variable on the enviorment
/// @param input The string passed
/// @param env The enviorment 
/// @return the length
long	len_expansion(char *input, char **env)
{
	char	*value;
	char	*search;
	long	len;
	bool	flag;

	len = 0;
	search = get_search(input, &flag);
	if (!search)
		return (-1);
	value = get_env(search, env);
	if (!value)
		return (free(search), 0);
	if (value)
		len = ft_strlen(value);
	free(search);
	return (len);
}
