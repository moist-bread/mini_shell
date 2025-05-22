
#include "../../Inc/minishell.h"

static	char	*process_expander(char *line, t_minishell ms);
static	void	here_doc_expansion(char *result, char *input, t_minishell ms);

char	*a_minha_funcao(t_minishell ms, char *line, char *limiter)
{
	char	*expanded;
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(line, '$') && (!ft_strchr(limiter, '\"') || !ft_strchr(limiter, '\'')))
		{
			expanded = process_expander(line, ms);
			if (!expanded)
				return (NULL);
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
	size_t	result_len;

	if (!line)
		return (ft_strdup(""));
	result_len = the_length (line, ms);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (NULL);
	here_doc_expansion(result, line, ms);
	return (result);
}

static	void	here_doc_expansion(char *result, char *input, t_minishell ms)
{
	int	i[2] = {0, 0};
	char	*exp;

	while (input[i[0]])
	{
		if (input[i[0]] == '$' && (ft_isalpha(input[i[0] + 1]) || input[i[0] + 1] == '_'))
		{
			exp = expansion(input + i[0], ms.env);
			if (exp)
			{
				ft_memcpy(result + i[1], exp, ft_strlen(exp));
				i[1] += ft_strlen(exp);
				free(exp);
			}
			while (input[++i[0]] && (input[i[0]] == '_' || ft_isalnum(input[i[0]])))
				;
		}
		else if (input[i[0]] == '$' && ft_isdigit(input[i[0] + 1]))
			i[0] += 2;
		else if (input[i[0]] == '$' && input[i[0] + 1] == '?')
			expansion_exit_status(result, i, ft_itoa(ms.exit_status));
		else
			result[i[1]++] = input[i[0]++];
	}
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
