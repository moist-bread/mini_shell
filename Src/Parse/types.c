

#include "../../Inc/minishell.h"

/// @brief Assigns a Type to the Node
/// @param token Node of a list 
void	assign_type_token(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (temp)
	{
		assigns_built_in(temp);
		assigns_types(temp);
		assigns_cmd_or_arg(temp);
		temp = temp->next;
	}
}

/// @brief Checks if the token received is a built_in
/// @param token Node of the list of tokens
void	assigns_built_in(t_token *token)
{
	if (ft_strncmp("echo", token->cont, 5) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("cd", token->cont, 3) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("pwd", token->cont, 4) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("export", token->cont, 8) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("unset", token->cont, 7) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("env", token->cont, 4) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("exit", token->cont, 5) == 0)
		token->type = BUILT_IN;
}

/// @brief checks if the token received is PIPE or REDIR
/// @param token Node of the list of tokens
void	assigns_types(t_token *token)
{
	if (ft_strncmp("|", token->cont, 2) == 0)
		token->type = PIPE;
	else if (ft_strncmp("<", token->cont, 2) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(">", token->cont, 2) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp("<<", token->cont, 3) == 0)
		token->type = REDIR_HERE_DOC;
	else if (ft_strncmp(">>", token->cont, 3) == 0)
		token->type = REDIR_OUT_APPEND;
}

/// @brief Checks if the token received CMD or ARG
/// @param token Node of the list of tokens
void	assigns_cmd_or_arg(t_token *token)
{
	if (token->prev == NULL && token->type != BUILT_IN && token->type != REDIR_IN \
		&& token->type != REDIR_OUT && token->type != REDIR_HERE_DOC && token->type != REDIR_OUT_APPEND)
		token->type = CMD;
	else if (token->prev && token->prev->type == REDIR_HERE_DOC && token->type != BUILT_IN \
		&& token->type != REDIR_IN && token->type != REDIR_OUT && token->type != PIPE \
		&& token->type != REDIR_HERE_DOC && token->type != REDIR_OUT_APPEND)
		token->type = LIM;
	else if (token->prev && token->prev->type == PIPE && token->type != BUILT_IN && token->type != REDIR_IN \
		&& token->type != REDIR_OUT && token->type != REDIR_HERE_DOC  && token->type != PIPE \
		&& token->type != REDIR_OUT_APPEND)
		token->type = CMD;
	else if (token->prev && (token->prev->type == CMD || token->prev->type == BUILT_IN || token->prev->type == REDIR_IN \
		|| token->prev->type == REDIR_OUT || token->prev->type == REDIR_HERE_DOC \
		|| token->prev->type == REDIR_OUT_APPEND))
	{
		token->type = ARG;
		assigns_types(token);
	}
}

/// @brief Assigns a name to the token, done for the debug
/// @param type Of the Node
void	assign_name(int type)
{
	if (type == 0)
		printf("Type: %s", "CMD");
	else if (type == 1)
		printf("Type: %s", "ARG");
	else if (type == 2)
		printf("Type: %s", "PIPE");
	else if (type == 3)
		printf("Type: %s", "REDIR_IN");
	else if (type == 4)
		printf("Type: %s", "REDIR_HERE_DOC");
	else if (type == 5)
		printf("Type: %s", "LIM");
	else if (type == 6)
		printf("Type: %s", "REDIR_OUT");
	else if (type == 7)
		printf("Type: %s", "REDIR_OUT_APPEND");
	else if (type == 8)
		printf("Type: %s", "BUILT_IN");
}
