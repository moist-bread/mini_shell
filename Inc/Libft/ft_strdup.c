/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:20:20 by andcarva          #+#    #+#             */
/*   Updated: 2024/10/29 12:17:00 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/* int	main(void)
{
	char original[] = "Hello, World!";
	char *duplicate;

	duplicate = ft_strdup(original);

	if (duplicate == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}

	printf("Original: %s\n", original);
	printf("Duplicate: %s\n", duplicate);

	return (0);
} */
