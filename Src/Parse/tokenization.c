

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
	// master_check();
	// return (token);
}

/// @brief Places a node in a list
/// @param input String received from the Stdout 
/// @param head Beggining of the list
/// @return The head of the list
void	place_token(char *input, t_token **head)
{
	t_token	*newtk;
	char	**tokens;
	int		i;

	*head = NULL;
	tokens = cracked_split(input, ' ');
	i = -1;
	while (tokens[++i])
	{
		newtk = newtoken(tokens[i]);
		tokenadd_back(head, newtk);
	}
}

/// @brief Assigns a Type to the Node
/// @param token Node of a list 
void	assign_type_token(t_token *token)
{
	t_token	*temp;

	if(!token)
		return ;
	temp = token;
	while (temp)
	{
		checks_built_in(temp);
		check_types(temp);
		check_cmd_or_arg(temp);
		temp = temp->next;
	}
}
