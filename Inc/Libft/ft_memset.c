/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:19:00 by andre             #+#    #+#             */
/*   Updated: 2024/10/29 12:16:24 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptrmem, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)ptrmem;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (ptrmem);
}

/* int main() 
{
    char str[50] = "Hello, World!";
    printf("Before memset: %s\n", str);
    
    // Fill the first 5 characters of the string with '*'
    
    ft_memset(str, '*', 5);
    printf("After ft_memset: %s\n", str);
	memset(str, '*', 5);
	printf("After memset: %s\n", str);
    
	return 0;
}  */
