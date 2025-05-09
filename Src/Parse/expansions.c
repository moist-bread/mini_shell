
#include "../../Inc/minishell.h"

char	*process_quote_expansions(char *input, char **env)
{	
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (!input)
			result = ft_strdup("");
	if (input[0] == '\"' || input[0] == '\'' || input[0] == '$')
			result = the_expansion(input, env);
	else
		result = ft_strdup(input);
	free(input);
	return (result);
}

char	*the_expansion(char	*input, char **env)
{
	char	*result;
	int		i;

	i = 0;
	if (input[0] == '$')

	while(input[i])
	{
		if (input[0] == '\'' && input[i] == '$')
			result = single_quote(input);
		else if (input[0] == '\"' && input[i] == '$')
			result = quote(input, env);
	}
	return (result);
}

char	*single_quote(char *input)
{
	char	*result;
	int		quote;
	int		i;

	quote = quote_count(input, false);
	result = ft_calloc(sizeof(char), ft_strlen(input) - quote);
	if (!result)
		return (NULL);
	i = 0;
	while (input[i] && input[i] == '\'')
		i++;
	while (input[i] && input[i] != '\'')
	{
		result[i] = input[i];
		i++;
	}
	return (result);
}

char	*quote(char *input, char **env)
{
	char	*result;
	char	*path;
	char	*search;
	int		quote;
	int		i;

	quote = quote_count(input, false);
	search = get_search(input);
	path = get_env(search, env);
	if (!path)
		return (ft_strdup(input));
	result = ft_calloc(sizeof(char), ft_strlen(path) + quote);
	if (!result)
		return (NULL);
	ft_strlcpy(result, path, ft_strlen(path));
	free(search);
	return (result);
}
