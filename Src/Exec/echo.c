
#include "../../Inc/minishell.h"

static int	echo_validate_options(char *arg);

/// @brief Echoes NODES's arguments and handles the option -n
/// @param ms Overarching Minishell Structure
/// @param node Current echo node to be executed
void	echo_built_in(t_minishell *ms, t_tree_node *node, int fd)
{
	int	n_opt;
	int	i;

	printf(YEL "\nEntering echo built in" DEF "\n\n");
	i = -1;
	while (node->right && node->right->cont.args[++i])
	{
		if (i == 0)
		{
			n_opt = echo_validate_options(node->right->cont.args[i]);
			if (n_opt)
				continue ;
		}
		if ((!n_opt && i > 0) || (n_opt && i > 1))
			ft_printf_fd(fd, " ");
		ft_printf_fd(fd, "%s", node->right->cont.args[i]);
	}
	if (!n_opt)
		ft_printf_fd(fd, "\n");
	ms->exit_status = 0;
}

/// @brief Checks if ARG is a valid -n option or just an argument
/// @param arg Possible option argument
/// @return 0 when invalid, 1 when valid
static int	echo_validate_options(char *arg)
{
	int	i;

	if (*arg == '-')
	{
		printf("verifying echo option\n");
		i = 0;
		while (arg[++i] == 'n')
			;
		if (!arg[i])
			return (1);
	}
	return (0);
}
