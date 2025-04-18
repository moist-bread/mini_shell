/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cracked_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:38:09 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/14 15:49:39 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_str(char const *s, char c)
{
	size_t	count;
	char	quote;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && (*s == '\'' || *s == '\"'))
		{
			quote = *s++;
			count++;
			while (*s && *s != quote)
				s++;
			while (*s == quote)
				s++;
		}
		else if (*s)
		{
			count++;
			while (*s && *s != c && *s != '\'' && *s != '\"')
				s++;
		}
	}
	return (count);
}

static void	working_quote(char const *s, int *len, char c)
{
	char	quote;
	int		start;

	*len = 0;
	while (s[*len] && s[*len] == c)
		(*len)++;
	if (s[*len] && (s[*len] == '\'' || s[*len] == '\"'))
	{
		quote = s[(*len)++];
		start = *len;
		while (s[*len] && s[*len] != quote)
			(*len)++;
		if (s[*len] == quote)
		{
			if (*len > start)
				(*len)++;
			else
				*len = start - 1;
		}
		else
			*len = start - 1;
	}
	else
		while (s[*len] && s[*len] != c && s[*len] != '\'' && s[*len] != '\"')
			(*len)++;
}

static char	*get_word(char const *s, char c)
{
	char	*new_word;
	int		len;

	len = 0;
	working_quote(s, &len, c);
	if (len == 0)
		return (NULL);
	new_word = malloc(sizeof(char) * (len + 1));
	if (!new_word)
		return (NULL);
	ft_strlcpy(new_word, s, len + 1);
	new_word[len] = '\0';
	return (new_word);
}

char	**cracked_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!split)
		return (NULL);
	while (s && *s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			working_quote(s, &len, c);
			if (len > 0)
			{
				split[i] = get_word(s, c);
				if (!split[i++])
					return (free_split(split), NULL);
				s += len;
			}
			else
				s++;
		}
	}
	split[i] = NULL;
	return (split);
}
