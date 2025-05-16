
#include "../../Inc/minishell.h"

char	*quote_remover(char *s)
{
	char	*str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(s) - quote_conter(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{	
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				str[j++] = s[i++];
			if(s[i] && s[i] == quote)
				i++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

/// @brief Counts the number of quotes that will seize to exist
/// @param s The string
/// @return The number of quotes
int	quote_conter(char *s)
{
	int		i;
	int		n;
	char	quote;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			n++;
			while (s[i] && s[i] != quote)
				i++;
			if(s[i] && s[i] == quote)
			{
				i++;
				n++;
			}
		}
		else
			i++;
	}
	return (n);
}
