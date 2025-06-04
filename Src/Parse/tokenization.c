/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:54:44 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 19:27:11 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Reads the input, adds a history, places a node in a list,
/// assigns a type and prints
/// @param input The string received from the Stdout
/// @return Input
char	*fake_readinput(t_minishell ms, char *input)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	input = readline(CYN "minishell > " DEF);
	if (!input)
	{
		printf(BLU "exit" DEF "\n");
		minishell_clean(ms, ms.exit_status);
	}
	add_history(input);
	return (input);
}

/// @brief Creates the list of tokens
/// @param input The string received from the Stdout
t_token	*create_tokens(char *input)
{
	t_token	*tokens;

	tokens = NULL;
	if (place_token(input, &tokens) == -1)
		minishell_clean(*mem_save(NULL), 1);
	assign_type_token(tokens, false);
	master_check(&tokens);
	free(input);
	return (tokens);
}

/// @brief Places a node in a list
/// @param input String received from the Stdout
/// @param head Beggining of the list
/// @return The head of the list
int	place_token(char *input, t_token **head)
{
	t_token	*newtk;
	char	**newinput;
	char	*updated_input;
	int		i;

	*head = NULL;
	if (!check_quotes(input))
		return (1);
	updated_input = add_spaces(input);
	if (!updated_input)
		return (-1);
	newinput = cracked_split(updated_input);
	free(updated_input);
	i = 0;
	while (newinput && newinput[i])
	{
		newtk = newtoken(newinput[i]);
		if (!newtk)
			return (free_split(newinput), -1);
		tokenadd_back(head, newtk);
		i++;
	}
	free_split(newinput);
	return (0);
}

/// @brief Adds spaces between operaters in the input
/// @param input String received from the Stdout
/// @return The new input with the spaces
char	*add_spaces(char *input)
{
	char	*newinput;
	int		len;

	len = space_length(input);
	newinput = space_put(input, len);
	if (!newinput)
		return (NULL);
	return (newinput);
}

void	syntax_clear(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		free(current->cont);
		free(current);
		current = next;
	}
	*token = NULL;
}

// /// @brief Prints the node in order, there type and content
// /// @param tokens The token of the list
// void	print_tokens(t_token *tokens)
// {
// 	t_token	*curr;
// 	int		i;

// 	if (!tokens)
// 		return ;
// 	curr = tokens;
// 	i = 0;
// 	while (curr)
// 	{
// 		printf("Token[%d]: %s", i, curr->cont);
// 		printf("\t");
// 		assign_name(curr->type);
// 		printf("\t");
// 		printf("(ID: %u)\n", curr->type);
// 		curr = curr->next;
// 		i++;
// 	}
// }
