

#include "../../Inc/minishell.h"

void	checks_built_in(t_token *token)
{
	if (ft_strncmp("echo", token->cont, 4) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("cd", token->cont, 2) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("pwd", token->cont, 3) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("export", token->cont, 7) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("unset", token->cont, 6) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("env", token->cont, 3) == 0)
		token->type = BUILT_IN;
	else if (ft_strncmp("exit", token->cont, 4) == 0)
		token->type = BUILT_IN;
}

void	check_types(t_token *token)
{
	if (ft_strncmp("|", token->cont, 1) == 0)
		token->type = PIPE;
	else if (ft_strncmp("<", token->cont, 1) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(">", token->cont, 1) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp("<<", token->cont, 2) == 0)
		token->type = REDIR_HERE_DOC;
	else if (ft_strncmp(">>", token->cont, 2) == 0)
		token->type = REDIR_OUT_APPEND;
}

void	check_cmd_or_arg(t_token *token)
{
	// if(token->type == PIPE)
	// 	token->next->type = CMD;
	// else if (token->type == REDIR_IN || token->type == REDIR_OUT \
	// 	 || token->type == REDIR_HERE_DOC || token->type == REDIR_OUT_APPEND)
	// {
	// 	if (token->next->type != ARG)
	// 		token->next->type = CMD;
	// 	else if (token->prev->type != BUILT_IN)
	// 		token->prev->type = CMD;
	// 	else
	// 		token->next->type = ARG;
	// }
	// else if ()

	if (token->prev == NULL && token->type != BUILT_IN && token->type != REDIR_IN\
		&& token->type != REDIR_OUT && token->type != REDIR_HERE_DOC && token->type != REDIR_OUT_APPEND)
		token->type = CMD;
	if (token->type == PIPE)
		token->next->type = CMD;	 
}

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
		printf("Type: %s", "REDIR_OUT");
	else if (type == 6)
		printf("Type: %s", "REDIR_OUT_APPEND");
	else if (type == 7)
		printf("Type: %s", "BUILT_IN");
}
