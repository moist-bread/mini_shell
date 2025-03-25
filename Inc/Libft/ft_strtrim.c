/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:30:45 by andcarva          #+#    #+#             */
/*   Updated: 2024/10/31 15:38:09 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_set(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned char	*src;
	size_t			i;
	size_t			start;
	size_t			end;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (s1[start] != '\0' && ft_set(set, s1[start]))
		start++;
	while (end > start && ft_set(set, s1[end - 1]))
		end--;
	src = (unsigned char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!src)
		return (NULL);
	while (start < end)
		src[i++] = s1[start++];
	src[i] = '\0';
	return ((char *)src);
}

/* int	main(void)
{

	char	*mal;

	mal = ft_strtrim("abcHelloabc", "z");
	printf("%s\n", mal);
} */