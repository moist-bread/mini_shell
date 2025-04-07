/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:09:12 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/03 15:09:19 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
}

/* int main() {
    char buffer[10];  // Array of 10 bytes

	int	i = 0;	
    while(i < 10) {
        buffer[i] = i + 1;
		i++;
    }

	int j = 0;
    printf("Buffer before ft_bzero:\n"); // Print buffer before calling ft_bzero
    while (j < 10) {
        printf("%d ", buffer[j]);
		j++;
    }
    printf("\n");

    // Call custom my_bzero function to zero out the buffer
    ft_bzero(buffer, 10);

    int k = 0;
    printf("Buffer after my_bzero:\n"); // Print buffer after calling my_bzero
    while (k < 10) {
        printf("%d ", buffer[k]);
		k++;
    }
    printf("\n");

    return 0;
} */
