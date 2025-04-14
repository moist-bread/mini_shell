

#include "../../Inc/minishell.h"

static	void	lenght_util(char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] && ft_isprint(input[*i]) && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote && input[*i + 1])
		(*i)++;
}

/// @brief Length of new input
/// @param input The string received from the Stdout
/// @return lenght
int	space_length(char *input)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (input[i])
	{
		if (input[i] && ft_strchr("\'\"", input[i]))
			lenght_util(input, &i);
		if (input[i] && ft_strchr("|<>", input[i]))
		{
			if (i > 0 && input[i - 1] != ' ' && !ft_strchr("|<>", input[i - 1]))
			{
				// printf("backspace%c i-1%c\n ", input[i], input[i - 1]);
				spaces++;
			}
			if (input[i] == input[i + 1])
				i++;
			if (input[i + 1] && input[i + 1] != ' ')
			{
				// printf("frontspace%c\n", input[i]);
				spaces++;
			}
			// printf("I:%c I1:%c\n", input[i],input[i+1]);
		}
		if (input[i])
			i++;
	}
	return (spaces);
}

/// @brief What happens between quotes, in my space_put function
/// @param input The string received from the Stdout
/// @param dest New string with the spaces
/// @param i increment
/// @param j increment
static	void	between_quotes(char *input, char *dest, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	dest[(*j)++] = input[(*i)++];
    while (ft_isprint(input[*i]) && input[*i] != quote)
        dest[(*j)++] = input[(*i)++];
    if (input[*i] == quote)
        dest[(*j)++] = input[(*i++)];
}

/// @brief What happens between quotes, in my space_put function
/// @param input The string received from the Stdout
/// @param dest New string with the spaces
/// @param i increment
/// @param j increment
static void	if_operators(char *input, char *dest, int *i, int *j)
{
	// if (*i > 0 && input[*i - 1] != ' ' && !ft_strchr("|<>", input[*i - 1]))
    //     dest[(*j)++] = ' ';
    // if (input[*i + 1] && input[*i] == input[*i + 1])
    //     dest[(*j)++] = input[(*i)++];
    // dest[(*j)++] = input[*i];
    // if (input[*i + 1] && input[*i + 1] != ' ')
    //     dest[(*j++)] = ' ';
	if (*i > 0 && input[*i - 1] != ' ' && !ft_strchr("|<>", input[*i - 1]))
		dest[(*j)++] = ' ';
	dest[(*j)++] = input[(*i)++];
	if (input[*i] && input[*i] == input[*i - 1])
		dest[(*j)++] = input[(*i)++];
	if (input[*i] && input[*i] != ' ')
		dest[(*j)++] = ' ';
}

/// @brief Functions adds a space before and after Pipes and Regirs
/// @param input The string received from the Stdout
/// @param len the number of spaces
/// @return the updated string with spaces
char	*space_put(char *input, int len)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = ft_calloc(len + ft_strlen(input) + 1, sizeof(char));
	while (input[i])
	{
		if (input[i] && (input[i] == '\"' || input[i] == '\''))
			between_quotes(input, dest, &i, &j);
		else if (input[i] && ft_strchr("|<>", input[i]))
		{
			if_operators(input, dest, &i, &j);
			continue;
		}
		else
			dest[j++] = input[i];
		if (input[i])
			i++;

	}
	dest[j] = '\0';
	return (dest);
}
