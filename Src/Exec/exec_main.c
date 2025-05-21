
#include "../../Inc/minishell.h"

char	*fake_readinput(t_minishell ms, char	*input);
t_tree_node	*fake_create_tree(t_token *tokens);
void	fake_clear_token_lst(t_token	*token);

int	main(int ac, char **av, char **env)
{
	t_minishell	ms;
	char		*input;
	t_token		*tokens;
	
	(void)ac;
	(void)av;

	ft_printf_fd(1, YEL "Testing executer WITH TREE main !" DEF "\n\n");
	minishell_struct_init(&ms, env);
	input = NULL;
	while(1)
	{
		// parsing
		input = fake_readinput(ms, input);
		tokens = create_tokens(input);
		ms.tree_head = fake_create_tree(tokens);
		fake_clear_token_lst(tokens);
		// execution
		master_distributer(&ms, ms.tree_head);
		if (ms.tree_head) // prep for next input
		{
			free_tree(ms.tree_head);
			ms.tree_head = NULL;
		}
	}
	minishell_clean(ms, ms.exit_status); // clean up
}

t_tree_node	*fake_create_tree(t_token *tokens)
{
	t_tree_node	*tree_node;
	
	printf("Entered Create Tree\n");
	tree_node = NULL;
	place_treenode(tokens, &tree_node, false);
	tree_apply_print(tree_node, 0, "Root");
	printf("\n");
	return (tree_node);
}
