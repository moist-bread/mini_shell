/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:22:04 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/11 14:20:01 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

char	**matrix_add_front(char *add, char **original)
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
		new[i + 1] = ft_strdup(original[i]);
		if (!new[i + 1])
			free_matrix((void **)new, i + 1);
	}
	if (original)
		new[i + 1] = NULL;
	else
		new[1] = NULL;
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
			free_matrix((void **)dup, i);
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

void	free_matrix(void **matrix, int max)
{
	int	i;

	i = 0;
	while (i <= max)
		free(matrix[i++]);
	free(matrix);
}
