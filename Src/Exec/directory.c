
#include "../../Inc/minishell.h"

/// @brief Print name of current/working directory
/// @param ms
/// @param node
void	pwd_built_in(t_minishell *ms, t_tree_node *node)
{
	printf(YEL "\nEntering pwd built in" DEF "\n\n");
	if (node->right && *node->right->cont.args[0] == '-'
		&& node->right->cont.args[0][1])
	{
		printf("pwd: -%c: invalid option\n", node->right->cont.args[0][1]);
		printf("pwd: usage: pwd\n");
		ms->exit_status = 2;
	}
	else
	{
		printf("%s\n", get_env("PWD=", &ms->env[ms->env_start]));
		ms->exit_status = 0;
	}
}

// chdir()
// change into the char *path directory, returns -1 when failure

// cd isto    
// cd: no such file or directory: isto (exit 1)

// cd isto aquilo
// cd: string not in pwd: isto (exit 1)
void	cd_built_in(t_minishell *ms, t_tree_node *node)
{
	printf(YEL "\nEntering cd built in" DEF "\n\n");
	if (node->right && *node->right->cont.args[0] == '-'
		&& node->right->cont.args[0][1])
	{
		printf("pwd: -%c: invalid option\n", node->right->cont.args[0][1]);
		printf("pwd: usage: pwd\n");
		ms->exit_status = 2;
	}
	else
	{
		printf("%s\n", get_env("PWD=", &ms->env[ms->env_start]));
		ms->exit_status = 0;
	}
}