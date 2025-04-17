
#include "../../Inc/minishell.h"

/// @brief Gets the Value associated with Name SEARCH
/// @param search Name for which to search in the existing ENV
/// @param env Environment
/// @return Value corresponding to SEARCH name
char	*get_env(char *search, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], search, ft_strlen(search)) != 0)
		i++;
	if (env[i]) // find a way to check if its within non export range or nah
		return ((env[i] + ft_strlen(search))); // aka its correctly formated
	return (NULL);
}

int		find_env(char *search, char **env)
{
	(void)search;
	(void)env;
	return(0);
}

int		replace_env()
{
	return(0);
}

char **env_add_back(char **env, char *add)
{
	(void)env;
	(void)add;
	return(NULL);
}

/// @brief Adds string ADD to the Beggining of matrix ORIGINAL
/// @param add String to be added
/// @param original Original matrix
/// @return New matrix (add + original)
char	**env_add_front(char *add, char **original)
{
	char	**new;
	int		i;

	if (!add && !original)
		return (NULL);
	if (!add)
		return (matrix_dup_char(original));
	new = malloc((ft_matrixlen(original) + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup(add);
	i = -1;
	while (original && original[++i])
	{
		new[i + 1] = original[i];
		if (!new[i + 1])
			free_matrix((void **)new, i + 1);
	}
	if (original)
		new[i + 1] = NULL;
	else
		new[1] = NULL;
	free (original);
	return (new);
}
