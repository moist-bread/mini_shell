
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

// cd Src     _ send it to chdir and check for success
// update pwd and oldpwd (exit 0)

// cd         _ path becomes HOME,send it to chdir and check for success
// update pwd and oldpwd (exit 0)

// cd isto     _ send it to chdir and check for failure
// cd: no such file or directory: isto (exit 1)

// cd isto aquilo _womp womp
// cd: too many arguments (exit 1)

// cd -a Src _womp womp
// cd: -a: invalid option

void	cd_built_in(t_minishell *ms, t_tree_node *node)
{
	char *path;

	printf(YEL "\nEntering cd built in" DEF "\n\n");
	
	
	if (node->right && *node->right->cont.args[0] == '-'
		&& node->right->cont.args[0][1]) // caso "cd -a coisa"
	{
		printf("cd: -%c: invalid option\n", node->right->cont.args[0][1]);
		ms->exit_status = 2;
		return ;
	}


	if (node->right && node->right->cont.args[1]) // caso "cd esta coisa"
	{
		printf("cd: too many arguments\n");
		ms->exit_status = 1;
		return ;
	}
		
		
	if (node->right) // caso "cd coisa"
		path = *node->right->cont.args;
	else // caso "cd"
		path = get_env("HOME=", &ms->env[ms->env_start]);
	
	
	if (chdir(path) == -1)
	{
		// failed change
		ms->exit_status = 1;
		return ;
	}
	else
	{
		// success in change
		printf("success in change\n");
		printf("env pwd: %s\n", get_env("PWD=", ms->env));
		printf("old pwd id: %d\n", get_env_idx(ms->env,"OLDPWD="));

		char *old = ft_strdup("OLDPWD=");
		char *new = ft_strdup("PWD=");

		// tou a fazer o meu replace de uma forma memso badalhoca
		replace_env_value(ms, old, get_env("PWD=", ms->env),
			get_env_idx(ms->env,"OLDPWD="));
		printf("old pwd succ\n");
		// if failed, cry
		

		replace_env_value(ms, new, getcwd(NULL, 0),
			get_env_idx(&ms->env[ms->env_start],"PWD="));
		printf("new pwd succ\n");
		// if failed, cry
		
		ms->exit_status = 0;
		return;
	}

}
