
#include "../../Inc/minishell.h"

static	char	*process_expander(char *line, t_minishell ms);
static	int	here_doc_expansion(char *result, char *input, t_minishell ms, char **exp);

char	*my_function(t_minishell ms, char *line, bool lim_flag)
{
	char	*expanded;
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(line, '$') && lim_flag == false)
		{
			expanded = process_expander(line, ms);
			if (!expanded)
				return (free(line), NULL);
			return (free(line), expanded);
		}
		else
			i++;
	}
	return (line);
}

static	char	*process_expander(char *line, t_minishell ms)
{
	char	*result;
	long	result_len;
	char	*exp;

	exp = NULL;
	if (!line)
		return (ft_strdup(""));
	result_len = the_length (line, ms, true); // prblem when is here_doc single_quotes;
	if (result_len == -1)
		return (NULL);
	if (result_len == 0)
		return (ft_strdup(""));
	printf("len_result: %zu\n", result_len);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (perror("malloc4"), NULL);
	if (here_doc_expansion(result, line, ms, &exp) == 1)
		return (free(result), NULL);
	return (result);
}

static	int	here_doc_expansion(char *result, char *s, t_minishell ms, char **exp)
{
	int		i[2];
	bool	flag;

	flag = false;
	ft_bzero(i, sizeof(i));
	while (s[i[0]])
	{
		if (s[i[0]] == '$' && (ft_isalpha(s[i[0] + 1]) || s[i[0] + 1] == '_'))
		{
			*exp = expansion(s + i[0], ms.env, &flag);
			if (flag)
				return (1);
			if (*exp)
				write_and_advance(result, &i[1], *exp);
			while (s[++i[0]] && (s[i[0]] == '_' || ft_isalnum(s[i[0]])))
				;
		}
		else if (s[i[0]] == '$' && ft_isdigit(s[i[0] + 1]))
			i[0] += 2;
		else if (s[i[0]] == '$' && s[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = s[i[0]++];
	}
	return (0);
}


void	expansion_exit_status(char *result, int *i, char *exit_status)
{
	int	n;

	n = 0;
	i[0] += 2;
	while (exit_status[n])
	{
		result[i[1]] = exit_status[n];
		n++;
		i[1]++;
	}
	free(exit_status);
}
