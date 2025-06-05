/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_func_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:53 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 16:37:22 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static void	quotes_quoted(char *quoted, int *j, char put, char between);

/// @brief Removes the quotes of the token
/// @param s The expanded string
/// @return The string without quotes
char	*quote_remover(char *s)
{
	char	*str;
	int		i[2];
	char	quote;

	ft_bzero(i, sizeof(i));
	str = ft_calloc(sizeof(char), (ft_strlen(s) - quote_conter_len(s)) + 1);
	if (!str)
		return (perror("malloc"), NULL);
	while (s[i[0]])
	{
		if (s[i[0]] == '\"' || s[i[0]] == '\'')
		{
			quote = s[i[0]++];
			while (s[i[0]] && s[i[0]] != quote)
				str[i[1]++] = s[i[0]++];
			if (s[i[0]] && s[i[0]] == quote)
				i[0]++;
		}
		else
			str[i[1]++] = s[i[0]++];
	}
	return (str);
}

/// @brief Counts the number of quotes that will seize to exist
/// @param s The string
/// @return The number of quotes
size_t	quote_conter_len(char *s)
{
	int		i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i++];
			len++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] && s[i] == quote)
			{
				i++;
				len++;
			}
		}
		else
			i++;
	}
	return (len);
}

char	*quote_limiter(char	*exp)
{
	char	*quoted;
	int		i;
	int		j;

	j = 0;
	i = 0;
	quoted = ft_calloc(sizeof(char), ft_strlen(exp) + quote_count(exp) + 1);
	if (!quoted)
		return (perror("malloc"), NULL);
	while (exp[i])
	{
		if (exp[i] == '\'')
			quotes_quoted(quoted, &j, '\'', '\"');
		else if (exp[i] == '\"')
			quotes_quoted(quoted, &j, '\"', '\'');
		else
			quoted[j++] = exp[i];
		i++;
	}
	return (quoted);
}

static void	quotes_quoted(char *quoted, int *j, char put, char between)
{
	quoted[(*j)++] = between;
	quoted[(*j)++] = put;
	quoted[(*j)++] = between;
}

int	quote_count(char *exp)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (exp[i])
	{
		if (exp[i] == '\'' || exp[i] == '\"')
			len++;
		i++;
	}
	if (len)
		len *= 2;
	return (len);
}
