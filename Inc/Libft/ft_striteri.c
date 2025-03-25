/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:48:02 by andcarva          #+#    #+#             */
/*   Updated: 2024/10/31 15:10:55 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* void	capitalize_alternate(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c -= 32;  // Convert lowercase to uppercase
}

int main()
{
    char str[] = "hello, world!";

    printf("Original string: %s\n", str);
    ft_striteri(str, capitalize_alternate);
    printf("Modified string: %s\n", str);

    return 0;
} */
