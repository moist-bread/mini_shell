/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_types_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:11 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 16:23:29 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Checks if the quotes are impar and gives an error if they are
/// @param input String
bool	check_quotes(char *input)
{
	int		i;
	int		quote;
	char	is_quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			is_quote = input[i++];
			quote++;
			while (input[i] && input[i] != is_quote)
				i++;
			if (input[i] && input[i++] == is_quote)
				quote++;
		}
		else
			i++;
	}
	if (quote % 2 != 0)
		return (ft_error_check(NULL, 2), false);
	return (true);
}

/// @brief If is Operator
/// @param token Node of the token list
/// @return True if is Operator, False if is not
bool	is_token(t_token *token)
{
	if (token->type == PIPE || token->type == RED_HD || token->type == RED_IN
		|| token->type == RED_OUT || token->type == RED_APP)
		return (true);
	return (false);
}

void	is_limtiter_or_arg(t_token **temp)
{
	if ((*temp)->cont == NULL)
		(*temp)->type = ARG;
	else if ((*temp)->type == RED_HD && (*temp)->next)
	{
		*temp = (*temp)->next;
		(*temp)->type = LIM;
	}
	else if (is_token(*temp) && (*temp)->next)
	{
		*temp = (*temp)->next;
		(*temp)->type = ARG;
		assigns_types(*temp, false);
	}
}
