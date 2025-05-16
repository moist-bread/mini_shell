
#include "../../Inc/minishell.h"

/// @brief  Compares two strings in their totality 
/// @return 0 when strings are equal, other values when different
int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
