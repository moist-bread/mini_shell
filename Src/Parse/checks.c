

#include "../../Inc/minishell.h"

static void	ft_copy(char *input, char *checked, int *i, int *j);

/// @brief The master function for the checks in the list of tokens 
/// @param token Node of a list 
void	master_check(t_token **token)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	while (temp)
	{
		if (temp->prev == NULL && temp->type == PIPE)
			ft_error_check(token);
		else if (temp->next && temp->type == PIPE && temp->next->type == PIPE)
			ft_error_check(token);
		else if (temp->next && temp->type != PIPE && is_token(temp) == true \
		&& is_token(temp->next) == true)
			ft_error_check(token);
		else if (is_token(temp) == true && temp->next == NULL)
			ft_error_check(token);
		if (!*token)
			return;
		temp = temp->next;
	}
}

char	*check_expansion(char *input)
{
	char	*checked;
	int		i;
	int		j;

	i = 0;
	j = 0;
	checked = ft_calloc(sizeof(char), (ft_strlen(input) - checked_len(input)) + 1);
	if (!checked)
		return (perror("malloc"), NULL);
	while (input[i])
	{
		while (input[i] && (input[i] == '\"' || input[i] == '\''))
			ft_copy(input, checked, &i, &j);
		if (input[i] == '$' && !ft_isalpha(input[i + 1]) && input[i + 1] != '_' \
		&& input[i + 1] != '?')
			i++;
		else if (input[i])
			checked[j++] = input[i++];
	}
	return (checked);
}

size_t	checked_len(char *input)
{
	int		i;
	size_t	len;
	char	quote;

	len = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == '\"' || input[i] == '\''))
		{
			quote = input[i++];
			while(input[i] && input[i] != quote)
				i++;
			i++;
		}
		if (input[i] == '$' && !ft_isalpha(input[i + 1]) && input[i + 1] != '_' \
		&& input[i + 1] != '?')
			len += 1;
		if (input[i])
			i++;
	}
	return (len);
}

static void	ft_copy(char *input, char *checked, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	checked[(*j)++] = input[(*i)++];
	while(input[*i] && input[*i] != quote)
		checked[(*j)++] = input[(*i)++];
	checked[(*j)++] = input[(*i)++];
}