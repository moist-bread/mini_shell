
#include "../../Inc/minishell.h"

static int	invalid_cd(t_tree_node *node, int *status);

/// @brief Changes directory according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current cd node to be executed
void	cd_built_in(t_minishell *ms, t_tree_node *node)
{
	char	*path;
	char	*cur;

	printf(YEL "\nEntering cd built in" DEF "\n\n");
	if (node->right && invalid_cd(node->right, &ms->exit_status))
		return ;
	if (node->right) // caso "cd coisa"
		path = *node->right->cont.args;
	else // caso "cd"
		path = get_env("HOME=", &ms->env[ms->env_start]);
	if (!path || chdir(path) == -1)
	{
		if (!path)
			printf("cd: HOME not set\n");
		else
			printf("perror: %s\n", path); // perror
		ms->exit_status = 1;
	}
	else
	{
		printf("old env oldpwd:\t%s\n", get_env("OLDPWD=", ms->env));
		printf("old env pwd:\t%s\n", get_env("PWD=", ms->env));
		replace_env_value(ms, "OLDPWD=", get_env("PWD=", ms->env),
			get_env_idx(ms->env, "OLDPWD="));
		cur = getcwd(NULL, 0);
		replace_env_value(ms, "PWD=", cur, get_env_idx(&ms->env[ms->env_start],
				"PWD="));
		free(cur);
		printf("new env oldpwd:\t%s\n", get_env("OLDPWD=", ms->env));
		printf("new env pwd:\t%s\n", get_env("PWD=", ms->env));
		ms->exit_status = 0;
	}
}

/// @brief Checks for invalid options or argument amount for cd built in
/// @param node ARG Node associated with a cd BUILT IN Node
/// @param status Exit Status
/// @return 1 when invalid, 0 when valid
static int	invalid_cd(t_tree_node *node, int *status)
{
	if (node->cont.args[0][0] == '-' && node->cont.args[0][1])
	{
		printf("cd: -%c: invalid option\n", node->cont.args[0][1]);
		*status = 2;
		return (1);
	}
	else if (node->cont.args[1]) // caso "cd esta coisa"
	{
		printf("cd: too many arguments\n");
		*status = 1;
		return (1);
	}
	return (0);
}

/// @brief Print name of current/working directory
/// @param ms Overarching Minishell Structure
/// @param node Current pwd node to be executed
void	pwd_built_in(t_minishell *ms, t_tree_node *node)
{
	char *pwd;

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
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		ms->exit_status = 0;
	}
}
