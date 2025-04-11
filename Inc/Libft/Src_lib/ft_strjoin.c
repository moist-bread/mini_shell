/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:35:49 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/10 15:06:38 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char const) * (len + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

/* int	main(void)
{
	char	*s1 = "Hello";
	char	*s2 = " World";
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	
	printf("Final: %s\n", s3);
} */
