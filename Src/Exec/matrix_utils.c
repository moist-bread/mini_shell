
#include "../../Inc/minishell.h"

static void	free_matrix(void **matrix, int max);

/// @brief Adds string ADD to the MATRIX on index IDX
/// @param matrix Char ** to be added to
/// @param add String to be added to MATRIX
/// @param idx Index for where to add
/// @param len Length of MATRIX
/// @return New MATRIX with added ADD
char	**matrix_add_to_index(char **matrix, char *add, size_t idx, size_t len)
{
	char	**new;
	int		i;
	int		j;

	if (!add || !matrix || len < 1 || idx > len + 1)
		return (matrix);
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	i = -1;
	j = -1;
	while (++i <= (int)len)
	{
		if (i == (int)idx)
		{
			new[++j] = ft_strdup(add);
			if (!new[j])
				return (free(new), perror("malloc"), NULL);
		}
		new[++j] = matrix[i];
	}
	free(matrix);
	return (new);
}

char	**matrix_add_front(char *add, char **original)
{
	char	**new;
	int		i;

	if ((!add && !original) || !add)
		return (NULL);
	new = ft_calloc(ft_matrixlen(original) + 2, sizeof(char *));
	if (!new)
		return (perror("malloc"), NULL);
	new[0] = ft_strdup(add);
	if (!new[0])
		return (perror("malloc"), free(new), NULL);
	i = -1;
	while (original && original[++i])
		new[i + 1] = original[i];
	if (original)
		new[i + 1] = NULL;
	else
		new[1] = NULL;
	free(original);
	return (new);
}

char	**matrix_dup_char(char **original_matrix)
{
	char	**dup;
	int		i;

	if (!original_matrix)
		return (NULL);
	dup = malloc((ft_matrixlen(original_matrix) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (original_matrix[++i])
	{
		dup[i] = ft_strdup(original_matrix[i]);
		if (!dup[i])
			return (free_matrix((void **)dup, i), NULL);
	}
	dup[i] = NULL;
	return (dup);
}

size_t	ft_matrixlen(char **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return (i);
	while (matrix[i])
		i++;
	return (i);
}

static void	free_matrix(void **matrix, int max)
{
	int	i;

	i = 0;
	while (i <= max)
		free(matrix[i++]);
	free(matrix);
}
