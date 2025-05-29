
#include "../../Inc/minishell.h"

static int	count_str(char const *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_sep(*s))
			s++;
		if (*s)
			count++;
		while (*s && !is_sep(*s))
			word_runner(&s);
	}
	return (count);
}

static char	*get_word(char const *s, int len)
{
	char	*new_word;

	if (len == 0)
		return (NULL);
	new_word = ft_calloc(len + 1, sizeof(char));
	if (!new_word)
		return (NULL);
	ft_strlcpy(new_word, s, len + 1);
	return (new_word);
}

char	**cracked_split(char const *s)
{
	char	**split;
	size_t	i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	split = ft_calloc(count_str(s) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (s && *s != '\0')
	{
		while (*s && is_sep(*s))
			s++;
		if (*s)
		{
			len = word_len(s);
			split[i] = get_word(s, len);
			if (!split[i++])
				return (free_split(split), NULL);
			s += len;
		}
	}
	return (split);
}

// static int	count_str(char const *s, char c)
// {
// 	size_t	count;
// 	char	quote;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s && (*s == '\'' || *s == '\"'))
// 		{
// 			quote = *s++;
// 			count++;
// 			while (*s && *s != quote)
// 				s++;
// 			while (*s == quote)
// 				s++;
// 		}
// 		else if (*s)
// 		{
// 			count++;
// 			while (*s && *s != c && *s != '\'' && *s != '\"')
// 				s++;
// 		}
// 	}
// 	return (count);
// }

// static char	*get_word(char const *s, char c)
// {
// 	char	*new_word;
// 	int		len;

// 	len = 0;
// 	working_quote(s, &len c);
// 	if (len == 0)
// 		return (NULL);
// 	new_word = malloc(sizeof(char) * (len + 1));
// 	if (!new_word)
// 		return (NULL);
// 	ft_strlcpy(new_word, s, len + 1);
// 	new_word[len] = '\0';
// 	return (new_word);
//}

// static void	working_quote(char const *s, int *len, char c)
// {
// 	char	quote;
// 	int		start;

// 	*len = 0;
// 	while (s[*len] && s[*len] == c)
// 		(*len)++;
// 	if (s[*len] && (s[*len] == '\'' || s[*len] == '\"'))
// 	{
// 		quote = s[(*len)++];
// 		start = *len;
// 		while (s[*len] && s[*len] != quote)
// 			(*len)++;
// 		if (s[*len] == quote)
// 				(*len)++;
// 		else
// 			*len = start - 1;
// 	}
// 	else
// 		while (s[*len] && s[*len] != c && s[*len] != '\'' && s[*len] != '\"')
// 			(*len)++;
// }

// char	**cracked_split(char const *s, char c)
// {
// 	char	**split;
// 	size_t	i;
// 	int		len;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	split = malloc(sizeof(char *) * (count_str(s, c) + 1));
// 	if (!split)
// 		return (NULL);
// 	while (s && *s != '\0')
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s)
// 		{
// 			working_quote(s, &len, c);
// 			if (len > 0)
// 			{
// 				split[i] = get_word(s, c);
// 				if (!split[i++])
// 					return (free_split(split), NULL);
// 				s += len;
// 			}
// 			else
// 				s++;
// 		}
// 	}
// 	split[i] = NULL;
// 	return (split);
// }
