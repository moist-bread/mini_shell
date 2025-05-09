
#include "../../Inc/minishell.h"

int	quote_count(char *input, bool flag)
{
	int	single_quote;
	int	quote;
	int	j;

	j = -1;
	quote = 0;
	if (flag == true)
	{
		while (input[++j] && input[j] == '\"')
			quote++;
		return (quote);
	}
	else
	{
		while (input[++j] && input[j] == '\'')
			single_quote++;
		return (single_quote);
	}
}

char	*get_search(char *input)
{
	char	*search;
	int		i;
	int		quote;

	i = 0;
	quote += quote_count(input, false);
	quote += quote_count(input, true);
	while (input[i] && (input[i] == '\"' || input[i] == '\'' || input[i] == '$'))
		i++;
	search = ft_calloc(sizeof(char), ft_strlen(input) - quote);
	if (!search)
		return (NULL);
	while (input[i] && (input[i] != '\"' || input[i] != '\''))
	{
		search[i] = input[i];
		i++;
	}
	search[i] = '=';
	return (search);
}
