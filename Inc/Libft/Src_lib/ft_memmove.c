/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:48:32 by andre             #+#    #+#             */
/*   Updated: 2025/04/03 15:09:19 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int					i;
	unsigned char		*d;
	unsigned const char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (d < s && (s || d))
	{
		while (i < (int)len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (s || d)
	{
		i = (int)len;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dest);
}

/* int main(void)
{
    char str[20] = "Hello, World!";
    printf("Original string: '%s'\n", str);

    // Using ft_memmove to overlap regions
    ft_memmove(str + 13, str, 6); 
    printf("After ft_memmove: '%s'\n", str);

    // Using standard memmove for comparison
    char str2[20] = "Hello, World!";
    memmove(str2 + 13, str2, 6);
    printf("After memmove: '%s'\n", str2);

    return 0;

} */
