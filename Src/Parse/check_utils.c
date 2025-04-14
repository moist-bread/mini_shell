
#include "../../Inc/minishell.h"

/// @brief Checks if the quotes are impar
/// @param input String
void	check_quotes(char *input)
{
	int	i;
	int quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
		exit (1);
}
