
#include "../../Inc/minishell.h"

// case 1 -- found quotes: correr pelo que esta dentro das quotes, e fazer expansao
// case 2 -- found pelica: correr e copiar
// case 3 -- found $: fazer expansao
// case 4 -- found other: copiar
// case 5 -- $?

char	*process_quote_expansions(char *input, char **env)
{	
	char	*result;
	size_t	result_len;

	if (!input)
		return (ft_strdup(""));
	result_len = the_lenght(input, env);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (NULL);
	the_expansion(input, env, result);
	// free(input);
	return (result);
}

void the_expansion(char *input, char **env, char *result)
{
	int		i[2] = {0, 0};

	while (input[i[0]])
	{
		if (input[i[0]] == '\"')
			expand_double_quotes(input, env, result, i);
		else if (input[i[0]] == '\'')
			expand_single_quotes(input, result, i);
		else
			expand_unquotes(input, env, result, i);
	}
}

void	expand_double_quotes(char *input, char **env, char *result, int *i)
{
	char	*exp;

	result[i[1]++] = input[i[0]++];
	while (input[i[0]] && input[i[0]] != '\"')
	{
		if (input[i[0]] == '$' && (ft_isalpha(input[i[0] + 1]) || input[i[0] + 1] == '_'))
		{
			exp = expansion(input + i[0], env);
			if (exp)
			{
				ft_strlcpy(result + i[1], exp, ft_strlen(exp) + 1);
				i[1] += ft_strlen(exp);
				free(exp);
			}
			while (input[++i[0]] && (input[i[0]] == '_' || ft_isalnum(input[i[0]])))
				;
		}
		else
			result[i[1]++] = input[i[0]++];
	}
	if (input[i[0]] == '\"')
		result[i[1]++] = input[i[0]++];
}

void	expand_single_quotes(char *input, char *result, int *i)
{
	result[i[1]++] = input[i[0]++];
	while (input[i[0]] && input[i[0]] != '\'')
		result[i[1]++] = input[i[0]++];
	if (input[i[0]] == '\'')
		result[i[1]++] = input[i[0]++];
}

void	expand_unquotes(char *input, char **env, char *result, int *i)
{
	char	*exp;

	while (input[i[0]] && input[i[0]] != '\"' && input[i[0]] != '\'')
	{
		if (input[i[0]] == '$' && (ft_isalpha(input[i[0] + 1]) || input[i[0] + 1] == '_'))
		{
			exp = expansion(input + i[0], env);
			if (!exp)
			{
				ft_strlcpy(result + i[1], exp, ft_strlen(exp) + 1);
				i[1] += ft_strlen(exp);
				free(exp);
			}
			while (input[++i[0]] && (input[i[0]] == '_' || ft_isalnum(input[i[0]])))
				;
		}
		else
			result[i[1]++] = input[i[0]++];
	}
}
