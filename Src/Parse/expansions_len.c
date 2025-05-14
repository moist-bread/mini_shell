
#include "../../Inc/minishell.h"

size_t	len_double_quotes(char *input, char **env, int *i)
{
	size_t len;
    size_t expansion_len;

	len = 1;
	expansion_len = 0;
	while (input[++(*i)] && input[*i] == '\"')
	{
		if (input[*i] == '$' && (isalpha(input[*i + 1]) || input[*i + 1] == '_'))
		{
			expansion_len += len_expansion(input + *i, env);
			while (input[++(*i)] == '_' || ft_isalnum(input[*i]))
				;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	if (input[*i] == '\"')
	{
        len++;
        (*i)++;
    }
	return (expansion_len + len);
}

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

size_t	len_unquoted(char *input, char **env, int *i)
{
	size_t	len;
	size_t	expansion_len;

	len = 0;
	expansion_len = 0;
	while (input[*i] && input[*i] != '\"' && input[*i] != '\'')
	{
		if (input[*i] == '$' && (isalpha(input[*i + 1]) || input[*i + 1] == '_'))
		{
			expansion_len += len_expansion(input + *i, env);
			while (input[++(*i)] == '_' || ft_isalnum(input[*i]))
				;
		}
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len + expansion_len);
}

size_t	the_lenght(char *input, char **env)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			len += len_double_quotes(input, env, &i);
		else if (input[i] == '\'')
			len += len_single_quote(input, &i);
		else
			len += len_unquoted(input, env, &i);
	}
	return (len);
}

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