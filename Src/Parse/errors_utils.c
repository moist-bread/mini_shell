/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:49 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 14:33:57 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

void	fake_clear_token_lst(t_token *token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = token;
	while (current)
	{
		next = current->next;
		if (current->type == PIPE || (current->type >= RED_IN
				&& current->type <= RED_APP))
			free(current->cont);
		free(current);
		current = next;
	}
}

void	len_exit_status(char *exit_status, long *len, int *i)
{
	*len += ft_strlen(exit_status);
	*i += 2;
	free(exit_status);
}

void	write_and_advance(char *result, int *res_idx, char *exp)
{
	size_t	len;

	len = ft_strlen(exp);
	ft_memcpy(result + *res_idx, exp, len);
	*res_idx += len;
	free(exp);
}

int	process_token_quotes(t_token *curr)
{
	char	*new_cont;
	char	*cont;

	if (curr->type == LIM && (ft_strchr(curr->cont, '\"')
			|| ft_strchr(curr->cont, '\'')))
	{
		cont = check_expansion(curr->cont);
		if (!cont)
			return (1);
		curr->quote = true;
		new_cont = quote_remover(cont);
		if (!new_cont)
			return (1);
		free(cont);
	}
	else
	{
		new_cont = quote_remover(curr->cont);
		if (!new_cont)
			return (1);
	}
	free(curr->cont);
	curr->cont = new_cont;
	return (0);
}

int	handle_variable_expansion(char *s, int *i, char *result, char **env)
{
	char	*exp;
	bool	flag;

	flag = false;
	if (s[i[0]] == '$' && (ft_isalpha(s[i[0] + 1]) || s[i[0] + 1] == '_'))
	{
		exp = expansion(s + i[0], env, &flag);
		if (flag)
			return (1);
		if (exp)
			write_and_advance(result, &i[1], exp);
		while (s[++i[0]] && (s[i[0]] == '_' || ft_isalnum(s[i[0]])))
			;
	}
	return (0);
}
