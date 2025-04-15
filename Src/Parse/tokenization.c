
#include "../../Inc/minishell.h"

/// @brief Reads the input, adds a history, places a node in a list, assigns a type and prints
/// @param input The string received from the Stdout
/// @return Input
char	*readinput(char	*input)
{
	input = readline("minishell > "); 
	if (!input)
	{
		free(input);
		exit(0);
	}
	add_history(input);
	if (ft_strncmp(input, "exit", 4) == 0)
		exit (0);
	return (input);
}

// t_token **create_tokens(char *input)

/// @brief Creates the list of tokens
/// @param input The string received from the Stdout
void	create_tokens(char *input)
{
	t_token *tokens;

	tokens = NULL;
	place_token(input, &tokens);
	assign_type_token(tokens);
	print_tokens(tokens);
	master_check(tokens);
	// return (token);
}

/// @brief Places a node in a list
/// @param input String received from the Stdout 
/// @param head Beggining of the list
/// @return The head of the list
void	place_token(char *input, t_token **head)
{
	t_token	*newtk;
	char	**newinput;
	char	*updated_input;
	int		i;

	*head = NULL;
	check_quotes(input);
	updated_input = add_spaces(input);
	newinput = cracked_split(updated_input, ' ');
	free(updated_input);
	i = 0;
	while (newinput[i])
	{
		newtk = newtoken(newinput[i]);
		tokenadd_back(head, newtk);
		i++;
	}
	free_split(newinput);
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
	printf("spaces: %d\n", len);
	return (newinput);
}

/// @brief Prints the node in order, there type and content
/// @param tokens The token of the list 
void	print_tokens(t_token *tokens)
{
	t_token	*curr;
	int		i;

	if (!tokens)
		return ;
	curr = tokens;
	i = 0;
	while (curr)
	{
		printf("Token[%d]: %s", i, curr->cont);
		printf("\t");
		assign_name(curr->type);
		printf("\t");
		printf("ID: %u\n", curr->type);
		curr = curr->next;
		i++;
	}
}
