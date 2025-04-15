

#include "../../Inc/minishell.h"

/// @brief Basic error function
/// @param token Node of the token list
void	ft_error_check(t_token *token)
{
	clear_token_lst(token);
	printf("Error of syntax\n");
	exit(1);
}