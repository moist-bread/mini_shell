
#include "../../Inc/minishell.h"

void	echo_built_in(t_minishell *ms, t_tree_node *node)
{
	int	n_flag;
	int	i;

	(void)ms;
	printf(YEL "\nEntering echo built in" DEF "\n\n");
	i = -1;
	while (node->right && node->right->cont.args[++i])
	{
		if (i == 0)
		{
			n_flag = echo_validate_options(node->right->cont.args[i]);
			if (!n_flag)
				continue ;
		}
		if ((n_flag == 1 && i > 0) || (n_flag == 0 && i > 1))
			printf(" ");
		printf("%s", node->right->cont.args[i]);
	}
	if (n_flag)
		printf("\n");
}

int	echo_validate_options(char *arg)
{
	int	i;

	if (*arg == '-')
	{
		printf("verifying option\n");
		i = 0;
		while (arg[++i] == 'n')
			;
		if (!arg[i])
			return (0);
	}
	return (1);
}
