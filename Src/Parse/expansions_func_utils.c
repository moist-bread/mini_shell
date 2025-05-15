
#include "../../Inc/minishell.h"

char	*quote_remover(char *s)
{
	char	*str;

	str = ft_calloc(sizeof(char), ft_strlen(s) - quote_conter(s));
	if (!str)
		return (NULL);
	

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
		if (s[i] == '\"' || '\'')
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
		i++;
	}
	return (n);
}
