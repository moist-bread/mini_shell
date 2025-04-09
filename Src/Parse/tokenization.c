

#include "../../Inc/minishell.h"

void	readinput(char	*input)
{
	t_token *token;

	token = NULL;
	input = readline("minishell > ");
	if (!input)
	{
		free(input);
		exit(0);
	}
	add_history(input);
	if (ft_strncmp(input, "exit", 4) == 0)
		exit (0);
	token = place_token(input, token);
	// printf("%s\n", token->cont);
	assign_type_token(token);
	print_tokens(token);
}

t_token	*place_token(char *input, t_token *head)
{
	t_token	*newtk;
	char	**tokens;
	int		i;

	head = NULL;
	tokens = cracked_split(input, ' ');
	i = -1;
	while (tokens[++i])
	{
		newtk = newtoken(tokens[i]);
		tokenadd_back(&head, newtk);
	}
	// print_tokens(head);
	return (head);
}

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
