
#include "../../Inc/minishell.h"

static char	**env_init(t_minishell *ms, char **old_env);
static char	**shell_level_updater(t_minishell *ms, int old_val);
static int	create_needed_vars(char ***env, int *env_start);
static int	assign_sh_lvl(char *value);

/// @brief Initializes the values of the Minishell Struct
/// @param ms Overarching Minishell Structure
/// @param env Environment recieved by the program
void	minishell_struct_init(t_minishell *ms, char **env)
{
	init_sigact(ms, 'P');
	ms->tree_head = NULL;
	ms->exit_status = 0;
	ms->env = env_init(ms, env);
	if (!ms->env)
	{
		ft_printf_fd(2, "malloc: failed memory allocation on initialization\n");
		exit(1);
	}
}

/// @brief Initializes the environment depending on the recieved OLD_ENV
/// @param ms Overarching Minishell Structure
/// @param old_env Old Environment recieved by the program
/// @return New Environemnt
static char	**env_init(t_minishell *ms, char **old_env)
{
	char	**env;
	int		sh_lvl;

	env = NULL;
	ms->env_start = 0;
	if (*old_env)
	{
		env = matrix_dup_char(old_env);
		if (!env)
			return (NULL);
	}
	sh_lvl = get_env_idx("SHLVL=", env);
	if (sh_lvl != -1)
	{
		ms->env = env;
		env = shell_level_updater(ms, sh_lvl);
	}
	else
		env = matrix_add_front("SHLVL=1", env);
	if (!env || create_needed_vars(&env, &ms->env_start) == -1)
		return (NULL);
	return (env);
}

static char	**shell_level_updater(t_minishell *ms, int shl_idx)
{
	char	*new_val;

	new_val = ft_itoa(assign_sh_lvl(ms->env[shl_idx] + 6));
	if (!new_val)
		return (free_split(ms->env), NULL);
	if (replace_env_value(ms, "SHLVL=", new_val, shl_idx) == -1)
		return (free(new_val), free_split(ms->env), NULL);
	free(new_val);
	return (ms->env);
}

static int	assign_sh_lvl(char *value)
{
	long	lvl;

	lvl = 0;
	if (long_check(value, &lvl))
	{
		if (lvl + 1 == INT_MAX)
			return (ft_printf_fd(2, SHLVL_WARN), 1);
		if (lvl < INT_MIN)
			return (1);
		else if (lvl < 0 || lvl >= INT_MAX)
			return (0);
		return (lvl + 1);
	}
	else
		return (1);
}

static int	create_needed_vars(char ***env, int *env_start)
{
	char	*temp;
	char	*cwd;

	temp = get_env("PWD=", *env);
	if (!temp)
	{
		cwd = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", cwd);
		free(cwd);
		if (!temp)
			return (free_split(*env), -1);
		*env = matrix_add_front(temp, *env);
		free(temp);
	}
	temp = get_env("PATH=", *env);
	if (!temp)
		*env = matrix_add_front(VAR_PATH, *env);
	temp = get_env("OLDPWD=", *env);
	if (!temp)
	{
		*env = matrix_add_front("OLDPWD", *env);
		*env_start = 1;
	}
	return (0);
}
