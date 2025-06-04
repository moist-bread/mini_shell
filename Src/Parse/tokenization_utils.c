/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:54:40 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 13:11:40 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Puts the node in the end of the list
/// @param tklst List of tokens
/// @param newtk The new token
void	tokenadd_back(t_token **tklst, t_token *newtk)
{
	t_token	*temptk;

	if (!newtk)
		return ;
	if (!*tklst)
	{
		*tklst = newtk;
		newtk->next = NULL;
		newtk->prev = NULL;
		return ;
	}
	temptk = *tklst;
	while (temptk->next)
		temptk = temptk->next;
	temptk->next = newtk;
	newtk->next = NULL;
	newtk->prev = temptk;
}

/// @brief Puts the node in the beggining of the list
/// @param tklst List of tokens
/// @param newtk New token
void	tokenadd_front(t_token **tklst, t_token *newtk)
{
	if (!newtk)
		return ;
	newtk->next = *tklst;
	newtk->prev = NULL;
	if (*tklst)
		(*tklst)->prev = newtk;
	*tklst = newtk;
}

/// @brief Creates a node named token
/// @param cont Content of the token
/// @return The new token
t_token	*newtoken(char *cont)
{
	t_token	*newtk;

	newtk = ft_calloc(1, sizeof(t_token));
	if (!newtk)
		return (perror("malloc11"), NULL);
	newtk->cont = ft_strdup(cont);
	newtk->next = NULL;
	newtk->prev = NULL;
	newtk->type = ARG;
	newtk->quote = false;
	return (newtk);
}

t_token	*join_token_list(t_token **head, t_token *curr, t_token *first_new)
{
	t_token	*last_new;

	last_new = first_new;
	if (curr->prev)
	{
		curr->prev->next = first_new;
		first_new->prev = curr->prev;
	}
	else
	{
		*head = first_new;
		first_new->prev = NULL;
	}
	while (last_new->next)
		last_new = last_new->next;
	if (curr->next)
	{
		last_new->next = curr->next;
		curr->next->prev = last_new;
	}
	else
	{
		last_new->next = NULL;
	}
	return (last_new->next);
}

t_token	*replace_expanded_token(t_token **head, t_token *curr, char **expanded)
{
	t_token	*first_new;
	t_token	*next;
	int		i;

	i = 0;
	next = NULL;
	first_new = NULL;
	if (!expanded[0])
		tokenadd_back(&first_new, newtoken(NULL));
	else
	{
		while (expanded[i])
		{
			tokenadd_back(&first_new, newtoken(expanded[i]));
			i++;
		}
	}
	next = join_token_list(head, curr, first_new);
	free(curr->cont);
	free(curr);
	return (next);
}
