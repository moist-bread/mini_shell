
#include "../../Inc/minishell.h"

void	env_built_in(t_minishell *ms, t_tree_node *node)
{
	printf(YEL "\nEntering env built in" DEF "\n\n");
	if (node->right)
	{
		if (*node->right->cont.args[0] == '-')
			printf("env: invalid option -- \'%s\'\n",
				node->right->cont.args[0]);
		else
			printf("env: invalid argument -- \'%s\'\n",
				node->right->cont.args[0]);
		return ;
	}
	print_env(*ms, 0);
}
