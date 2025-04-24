

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
