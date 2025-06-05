/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_quick_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:51:37 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 12:48:33 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static void	ft_string_swap(char **a, char **b);
static void	matrix_quick_sort(char **qs, int start, int pivot);

/// @brief Makes a sorted copy of ORIGINAL using Quick Sort
/// @param original Matrix to be Sorted
/// @param len Length of Matrix
/// @note (the individual strings are not duplicated)
char	**sort_matrix(char **original, int len)
{
	char	**sorted;
	int		i;
	int		mid;

	sorted = ft_calloc(len + 1, sizeof(char *));
	if (!sorted)
		return (perror("malloc"), NULL);
	i = -1;
	while (original[++i])
		sorted[i] = original[i];
	mid = len / 2;
	if (sorted[0] > sorted[mid] && sorted[0] > sorted[len - 1])
		ft_string_swap(&sorted[0], &sorted[mid]);
	if (sorted[len - 1] > sorted[0] && sorted[len - 1] > sorted[mid])
		ft_string_swap(&sorted[mid], &sorted[len - 1]);
	if (sorted[0] > sorted[len - 1])
		ft_string_swap(&sorted[0], &sorted[len - 1]);
	matrix_quick_sort(sorted, 0, len - 1);
	return (sorted);
}

static void	ft_string_swap(char **a, char **b)
{
	char	*swp;

	swp = *a;
	*a = *b;
	*b = swp;
}

static void	matrix_quick_sort(char **qs, int start, int pivot)
{
	int	i;
	int	j;

	if (start < pivot)
	{
		i = start - 1;
		j = start - 1;
		while (++i <= pivot)
		{
			if (ft_strcmp(qs[i], qs[pivot]) <= 0)
			{
				j++;
				if (ft_strcmp(qs[i], qs[j]) < 0)
					ft_string_swap(&qs[i], &qs[j]);
			}
		}
		matrix_quick_sort(qs, start, j - 1);
		matrix_quick_sort(qs, j + 1, pivot);
	}
}
