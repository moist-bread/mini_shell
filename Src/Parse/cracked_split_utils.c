/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cracked_split_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:45:31 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 13:45:32 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief
/// @param c
/// @return
bool	is_sep(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

/// @brief
/// @param s
/// @return
int	word_len(const char *s)
{
	int	quote_len;
	int	len;

	len = 0;
	while (*s && is_sep(*s))
		s++;
	while (*s && !is_sep(*s))
	{
		quote_len = skip_quote(s);
		if (quote_len > 0)
		{
			len += quote_len;
			s += quote_len;
		}
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}

/// @brief
/// @param s
/// @return
int	skip_quote(const char *s)
{
	int		i;
	char	quote;

	if (!s || (s[0] != '\'' && s[0] != '\"'))
		return (0);
	i = 0;
	quote = s[i++];
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] && s[i] == quote)
		i++;
	return (i);
}

/// @brief
/// @param s
void	word_runner(const char **s)
{
	int	skip;

	skip = 0;
	if ((**s == '\'' || **s == '\"'))
	{
		while (**s && !is_sep(**s))
		{
			skip = skip_quote(*s);
			if (skip > 0)
				(*s) += skip;
			else
				(*s)++;
		}
	}
	else
		(*s)++;
}
