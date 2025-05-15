
#include "../../Inc/minishell.h"

/// @brief Receives the expanded string and puts in a new token
/// @param input The string passed
/// @param env The enviorment 
/// @param newtk New token
/// @param head Head of the token list
void	input_expander(char *input, char **env, t_token *newtk, t_token **head)
{
	char	*expanded;
	int		is_quote;
	// char	**final_result;
	// int		i;

	(void)newtk;
	(void)head;
	is_quote = 0;
	// step 1 -- expandir o char *
	expanded = process_quote_expansions(input, env, &is_quote);
	printf("result: %s\n", expanded);
	free(expanded);
	// // step 2 -- separate spaces if is not btween " or ', remove the " and '; 
	// final_result = separator(expanded, is_quote);
	// i = 0;
	// while (final_result[i])
	// {
	// 	newtk = newtoken(final_result[i]);
	// 	tokenadd_back(head, newtk);
	// 	i++;
	// }
}

/// @brief Searches for the variable name
/// @param input The string passed
/// @return The variable name
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

/// @brief Gets the expanded value from the eviorment
/// @param input The string passed
/// @param env The enviorment 
/// @return The expanded value
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

/// @brief Separates the expanded string and removes the quotes
/// @param expanded Expanded string
/// @param is_quote If is a quoted string or not
/// @return The new unquoted string
char	**separator_3000(char *expanded, int is_quote)
{
	char	**result;
	char 	**final_result;
	int		i;

	if (is_quote == 0)
		result = cracked_split(expanded);
	else
		result[0] = ft_strdup(expanded);
	free(expanded);
	i = 0;
	while (result[i])
	{
		final_result[i] = quote_remover(result[i]);
		i++;
	}
	free_split(result);
	return (final_result);
}


