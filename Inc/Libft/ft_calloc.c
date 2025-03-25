/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:46:54 by andcarva          #+#    #+#             */
/*   Updated: 2024/11/08 20:40:04 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (num == 0 || size == 0)
		return (NULL);
	if (num && (ULONG_MAX / num < size))
		return (NULL);
	total_size = num * size;
	if (total_size > INT_MAX)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	if (size == 0)
		return (ptr);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

/* int main() {
    size_t n = 0;
    int* arr = (int*) ft_calloc(n, sizeof(int));
	size_t i = 1;

    if (arr == NULL) 
	{
        printf("Memory allocation failed\n");
        return 1;
    }
    while(i < n) 
	{
        printf("arr[%zu] = %d\n", i, arr[i]);
		i++;
    }
    free(arr);
    return 0;
} */