
#include "../../Inc/minishell.h"

/// @brief Allocs a duplicate string of size N of SRC
char	*ft_strndup(char *src, size_t n)
{
	size_t		i;
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
