/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:48:43 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/23 19:21:54 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (little[j] != '\0' && j + i < len && big[i + j] == little[j])
				j++; 
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}

/* int	main(void)
{
	char	strbig[] = "Hello, my name is Andre";
	char	strlit[] = "name";
	char	*result;

	result = ft_strnstr(strbig, strlit, 14);
	printf("%s\n", result);	
} */
