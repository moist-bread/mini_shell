
#include "../../Inc/minishell.h"

static int	echo_validate_options(char *arg);

/// @brief Echoes NODES's arguments and handles the option -n
/// @param ms Overarching Minishell Structure
/// @param node Current echo node to be executed
void	echo_built_in(t_minishell *ms, t_tree_node *node)
{
	int	n_flag;
	int	i;

	printf(YEL "\nEntering echo built in" DEF "\n\n");
	(void)ms;
	i = -1;
	while (node->right && node->right->cont.args[++i])
	{
		if (i == 0)
		{
			n_flag = echo_validate_options(node->right->cont.args[i]);
			if (n_flag)
				continue ;
		}
		if ((!n_flag && i > 0) || (n_flag && i > 1))
			printf(" ");
		printf("%s", node->right->cont.args[i]);
	}
	if (!n_flag)
		printf("\n");
}

/// @brief Checks if ARG is a valid -n option or just an argument
/// @param arg Possible option argument
/// @return 0 when invalid, 1 when valid
static int	echo_validate_options(char *arg)
{
	int	i;

	if (*arg == '-')
	{
		printf("verifying option\n");
		i = 0;
		while (arg[++i] == 'n')
			;
		if (!arg[i])
			return (1);
	}
	return (0);
}
