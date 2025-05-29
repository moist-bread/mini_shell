
#include "../../Inc/minishell.h"

static int	invalid_cd(t_tree_node *node, int *status);
static void	cd_update_pwd(t_minishell *ms);

/// @brief Changes directory according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current cd node to be executed
void	cd_built_in(t_minishell *ms, t_tree_node *node)
{
	char	*path;

	// printf(YEL "\nEntering cd built in" DEF "\n\n");
	if (node->right && invalid_cd(node->right, &ms->exit_status))
		return ;
	if (node->right) // caso "cd coisa"
		path = *node->right->cont.args;
	else // caso "cd"
		path = get_env("HOME=", &ms->env[ms->env_start]);
	if (!path || chdir(path) == -1)
	{
		ft_printf_fd(2, "cd: ");
		if (!path)
			ft_printf_fd(2, "HOME not set\n");
		else
			perror(path);
		ms->exit_status = 1;
	}
	else
		cd_update_pwd(ms);
}

/// @brief Checks for invalid options or argument amount for cd built in
/// @param node ARG Node associated with a cd BUILT IN Node
/// @param status Exit Status
/// @return 1 when invalid, 0 when valid
static int	invalid_cd(t_tree_node *node, int *status)
{
	if (node->cont.args[0][0] == '-' && node->cont.args[0][1])
	{
		ft_printf_fd(2, "cd: -%c: invalid option\n", node->cont.args[0][1]);
		*status = 2;
		return (1);
	}
	else if (node->cont.args[1]) // caso "cd esta coisa"
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		*status = 1;
		return (1);
	}
	return (0);
}

/// @brief Updates values of the variables PWD and OLDPWD in the environment
/// @param ms Overarching Minishell Structure
static void	cd_update_pwd(t_minishell *ms)
{
	int		old_pi;
	int		env_len;
	char	*cur;

	// printf("old env oldpwd:\t%s\n", get_env("OLDPWD=", ms->env));
	// printf("old env pwd:\t%s\n", get_env("PWD=", ms->env));
	old_pi = get_env_idx("OLDPWD=", ms->env);
	if (old_pi == -1)
	{
		env_len = (int)ft_matrixlen(ms->env);
		ms->env = matrix_add_to_index(ms->env, "OLDPWD=", env_len, env_len);
		old_pi = env_len;
	}
	replace_env_value(ms, "OLDPWD=", get_env("PWD=", ms->env), old_pi);
	cur = getcwd(NULL, 0);
	replace_env_value(ms, "PWD=", cur, get_env_idx("PWD=", ms->env));
	free(cur);
	ms->exit_status = 0;
	// printf("new env oldpwd:\t%s\n", get_env("OLDPWD=", ms->env));
	// printf("new env pwd:\t%s\n", get_env("PWD=", ms->env));
}

/// @brief Print name of current/working directory
/// @param ms Overarching Minishell Structure
/// @param node Current pwd node to be executed
/// @param fd possible redir file descriptor
void	pwd_built_in(t_minishell *ms, t_tree_node *node, int fd)
{
	char	*pwd;

	// printf(YEL "\nEntering pwd built in" DEF "\n\n");
	if (node->right && *node->right->cont.args[0] == '-'
		&& node->right->cont.args[0][1])
	{
		ft_printf_fd(2, "pwd: -%c: invalid option\n",
			node->right->cont.args[0][1]);
		ft_printf_fd(2, "pwd: usage: pwd\n");
		ms->exit_status = 2;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ms->exit_status = 1;
		ft_printf_fd(fd, "%s\n", pwd);
		free(pwd);
		ms->exit_status = 0;
	}
}
