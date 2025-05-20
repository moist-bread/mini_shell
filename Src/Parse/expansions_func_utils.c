
#include "../../Inc/minishell.h"

/// @brief Removes the quotes of the token
/// @param s The expanded string
/// @return The string without quotes
char	*quote_remover(char *s)
{
	char	*str;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), (ft_strlen(s) - quote_conter_len(s)) + 1);
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
size_t	quote_conter_len(char *s)
{
	int			i;
	size_t		len;
	char		quote;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			len++;
			while (s[i] && s[i] != quote)
				i++;
			if(s[i] && s[i] == quote)
			{
				i++;	
				len++;
			}
		}
		else
			i++;
	}
	return (len);
}

void	len_exit_status(char *exit_status, size_t *len, int *i)
{
	*len += ft_strlen(exit_status);
	*i += 2;
	free(exit_status);
}

void	expansion_exit_status(char *result, int *i, char *exit_status)
{
	int	n;

	n = 0;
	i[0] += 2;
	while (exit_status[n])
	{
		result[i[1]] = exit_status[n];
		n++;
		i[1]++;
	}
	free(exit_status);
}