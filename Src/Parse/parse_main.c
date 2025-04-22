

#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input = NULL;
	t_token		*tokens;

	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Parse Main !\n" DEF);
	while(1)
	{
		input = readinput(input);
		tokens = create_tokens(input);
		create_tree(tokens);
		clear_token_lst(tokens);
	}
	return (0);
}

// Split needs an upgrade. It needs to separate in spaces, pipes and redirections
// If is echo arguments appear with spaces even if i dindt have a space in the prompt
// Example:
// 			"echo ola>fd banana" - writes - "ola banana"
// Example:
// 			"''hola'''''''hola''''" - writes - 1:"hola"  2:"hola"