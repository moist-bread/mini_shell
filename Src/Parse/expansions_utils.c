
#include "../../Inc/minishell.h"

void	input_expander(char *input, char **env, t_token *newtk, t_token **head)
{
	char	*expanded;
	// char	**final_result;
	// int		i;

	(void)newtk;
	(void)head;

	// step 1 -- expandir o char *
	expanded = process_quote_expansions(input, env);
	printf("result: %s\n", expanded);
	free(expanded);
	// // step 2 -- separate spaces if is not btween " or ', remove the " and '; 
	// final_result = separ(expanded);
	// i = 0;
	// while (final_result[i])
	// {
	// 	newtk = newtoken(final_result[i]);
	// 	tokenadd_back(head, newtk);
	// 	i++;
	// }
}

char	*get_search(char *input)
{
	char	*search;
	int		i;
	int		search_len;
	
	i = 0;
	search_len = 0;
	while (input[i] && input[i] != '$')
		i++;
	if (!input[i])
		return (NULL);
	i++;
	while (input[i + search_len] && (input[i + search_len] == '_' || ft_isalnum(input[i + search_len])))
		search_len++;
	search = ft_calloc(sizeof(char), search_len + 2);
	if (!search)
		return (NULL);
	ft_strlcpy(search, input + i, search_len + 1);
	search[search_len] = '=';
	return (search);
}
	
char	*expansion(char *input, char **env)
{
	char	*value;
	char	*search;
	char	*result;
	
	search = get_search(input);
	if (!search)
		return (NULL);
	value = get_env(search, env);
	if (!value)
		return (free(search), NULL);
	free(search);
	result = ft_strdup(value);
	if (!result)
		return (NULL);
	return (result);
}