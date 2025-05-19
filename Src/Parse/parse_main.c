

#include "../../Inc/minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_minishell	ms;
// 	char		*input = NULL;
// 	t_token		*tokens;

// 	(void)ac;
// 	(void)av;
// 	(void)env;
// 	printf(YEL "Parse Main !\n" DEF);
// 	minishell_struct_init(&ms, env);
// 	while(1)
// 	{
// 		input = readinput(input);
// 		tokens = create_tokens(input, env);
// 		ms.tree_head = create_tree(tokens);
// 		clear_token_lst(tokens);
// 		// if (ms.tree_head)
// 		// {
// 		// 	free_tree(ms.tree_head);
// 		// 	ms.tree_head = NULL;
// 		// }
// 	}
// 	return (0);
// }
