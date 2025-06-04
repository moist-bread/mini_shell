/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:54:09 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 16:57:15 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Receives the expanded string and puts in a new token
/// @param input The string passed
/// @param env The enviorment
/// @param newtk New token
/// @param head Head of the token list
char	**input_expander(char *input, t_minishell ms)
{
	char	*expanded;
	int		is_quote;
	char	**final_result;

	is_quote = 1;
	expanded = process_quote_expansions(input, ms, &is_quote);
	if (!expanded)
		return (NULL);
	final_result = separator_3000(expanded, is_quote);
	if (!final_result)
		return (NULL);
	return (final_result);
}

/// @brief Searches for the variable name
/// @param input The string passed
/// @return The variable name
char	*get_search(char *input, bool *flag)
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
	while (input[i + search_len] && (input[i + search_len] == '_'
			|| ft_isalnum(input[i + search_len])))
		search_len++;
	search = ft_calloc(sizeof(char), search_len + 2);
	if (!search)
	{
		*flag = true;
		return (perror("malloc5"), NULL);
	}
	ft_strlcpy(search, input + i, search_len + 1);
	search[search_len] = '=';
	return (search);
}

/// @brief Gets the expanded value from the eviorment
/// @param input The string passed
/// @param env The enviorment
/// @return The expanded value
char	*expansion(char *input, char **env, bool *flag)
{
	char	*value;
	char	*search;
	char	*result;

	search = get_search(input, flag);
	if (!search)
		return (NULL);
	value = get_env(search, env);
	if (!value)
		return (free(search), NULL);
	free(search);
	result = ft_strdup(value);
	if (!result)
	{
		*flag = true;
		return (perror("malloc6"), NULL);
	}
	return (result);
}

/// @brief Separates the expanded string and removes the quotes
/// @param expanded Expanded string
/// @param is_quote If is a quoted string or not
/// @return The new unquoted string
char	**separator_3000(char *expanded, int is_quote)
{
	char	**final_result;
	char	*quoted;

	final_result = NULL;
	quoted = quote_limiter(expanded);
	free(expanded);
	if (!quoted)
		return (NULL);
	if (is_quote == 0)
		final_result = separate(quoted);
	else
	{
		final_result = ft_calloc(sizeof(char *), 2);
		if (!final_result)
			return (perror("malloc7"), free(quoted), NULL);
		final_result[0] = quote_remover(quoted);
		if (!final_result[0])
			return (free(quoted), free_split(final_result), NULL);
		final_result[1] = NULL;
	}
	return (free(quoted), final_result);
}

/// @brief Does the separation with split
/// @param expanded The string already expanded
/// @return The splited expanded string
char	**separate(char *expanded)
{
	char	**result;
	char	**final_result;
	int		count;
	int		i;

	i = -1;
	count = 0;
	result = cracked_split(expanded);
	if (!result)
		return (NULL);
	while (result[count])
		count++;
	final_result = ft_calloc(sizeof(char *), count + 1);
	if (!final_result)
		return (perror("malloc8"), free_split(result), NULL);
	while (++i < count)
	{
		final_result[i] = quote_remover(result[i]);
		if (!final_result[i])
			return (free_split(final_result), free_split(result), NULL);
	}
	final_result[count] = NULL;
	free_split(result);
	return (final_result);
}
