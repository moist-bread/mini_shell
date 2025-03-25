/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:07:09 by andcarva          #+#    #+#             */
/*   Updated: 2025/03/13 17:37:04 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	count_str(char const *s, char c)
{
	size_t	count;
	size_t	word;

	word = 0;
	count = 0;
	while (s && *s != '\0')
	{
		while (s && *s != c && word == 0)
		{
			word = 1;
			count++;
		}
		if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	size_t	len;
	char	*new_word;
	size_t	i;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	new_word = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_word)
	{
		free_split(&new_word);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_word[i] = s[i];
		i++;
	}
	new_word[len] = '\0';
	return (new_word);
}

/* char	**ft_split2(char *s, char c, char **list, int count)
{
	size_t	num;
	char	*str;

	num = 0;
	while (s && *s && *s == c)
		s++;
	while (s && s[num]  && s[num] != c)
		num++;
	str = ft_substr(s, 0, num);
	s += num;
	if (s && *s)
		list = ft_split2(s, c, list, count + 1);
	else
		list = ft_calloc(count + 1, sizeof(char *));
	list[count] = str;
	return (list);
} */

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;

	i = 0;
	split = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!split)
		return (NULL);
	while (s && *s != '\0' && *s != '\n')
	{
		if (*s != c)
		{
			split[i] = get_word(s, c);
			if (!split[i])
				return (free_split(split), NULL);
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}

// char	**ft_split3(char const *str, char c)
// {
// 	size_t	cnt_word;
// 	char	*string;
// 	int		cnt;

// 	cnt_word = 0;
// 	while (str && *str
// 	{
// 		while (*str == c)
// 			str++;
// 		if (*str == '\0')
// 			cnt++;
// 		while (*str != c)
// 			str++;
// 	}
// 	while (str[cnt_word] && str[cnt_word] != c)
// 		cnt_word++;
// 	string = ft_substr(str, 0, cnt_word);
// 	str += cnt_word;
// 	if (str && *str)
// 		split = ft_split3(str, c, split, count + 1);
// 	else
// 	{
		
// 		split = ft_calloc(count + 1, sizeof(char *));
// 		if (!split)
// 			return (NULL);
// 	}
// 	split[cnt_word] = NULL;
// 	return (split);
// }

// int	main(void)
// {
// 	char	**split = ft_split3("Hello Word", ' ', split, 3);
// 	int	i = 0;

// 	while (split[i])
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	printf("%s\n", split[0]);
// }
