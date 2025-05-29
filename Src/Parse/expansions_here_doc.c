
#include "../../Inc/minishell.h"

static	char	*process_expander(char *line, t_minishell ms);
static	void	here_doc_expansion(char *result, char *input, t_minishell ms);

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
	size_t	result_len;

	if (!line)
		return (ft_strdup(""));
	result_len = the_length (line, ms);
	result = ft_calloc(sizeof(char), result_len + 1);
	if (!result)
		return (perror("malloc"), NULL);
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
