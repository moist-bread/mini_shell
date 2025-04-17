

#include "../../Inc/minishell.h"

/// @brief 
/// @param c 
/// @return 
bool is_sep(char c)
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
		if (*s && (quote_len = skip_quote(s)) > 0)
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
	if(s[i] && s[i] == quote)
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
			if ((skip = skip_quote(*s)) > 0)
				(*s) += skip;
			else
				(*s)++;
		}
	}
	else
		(*s)++;
}