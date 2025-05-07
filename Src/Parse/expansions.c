

#include "../../Inc/minishell.h"

char	*process_quote_expansions(char *input, char **env)
{
	// int		i;
	char	*result;

	// i = 0;
	result = NULL;
	if (input[0] == '\"' || input[0] == '\'')
	{
		while (*input ==  '\"' || *input ==  '\'')
			input++;
		if (*input == "\0")
			result = ft_strdup("");
		else
			result = the_expansion(input, env);
	}
	else
		result = ft_strdup(input);
	free(input);
	return (result);
}

char	*the_expansion(char	*input, char **env)
{
	char	*result;

	while(input)
	{
		if (*input == '$')
		{
			input++;
		}
	}
	return (result);
}

