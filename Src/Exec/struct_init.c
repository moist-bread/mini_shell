
#include "../../Inc/minishell.h"

static char	**env_init(t_minishell *ms, char **old_env);
static char	**shell_level_updater(t_minishell *ms, char *old_val);
static int	assign_sh_lvl(char *value);
static char	**env_i_case(t_minishell *ms);

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
	ms->quote = false; // MY FUNCTION
}

/// @brief Initializes the environment depending on the recieved OLD_ENV
/// @param ms Overarching Minishell Structure
/// @param old_env Old Environment recieved by the program
/// @return New Environemnt 
static char	**env_init(t_minishell *ms, char **old_env)
{
	char	**env;
	char	*sh_lvl;

	env = NULL;
	if (*old_env)
	{
		ms->env_start = 0;
		env = matrix_dup_char(old_env);
		if (!env)
			return (NULL);
		sh_lvl = get_env("SHLVL=", env);
		if (sh_lvl)
		{
			ms->env = env;
			shell_level_updater(ms, sh_lvl);
		}
		else
			env = matrix_add_front("SHLVL=1", env);
		return (env);
	}
	else
		return (env_i_case(ms));
}

static char	**shell_level_updater(t_minishell *ms, char *old_val)
{
	char	*new_val;

	new_val = ft_itoa(assign_sh_lvl(old_val));
	if (!new_val)
		return (free_split(ms->env), NULL);
	if (replace_env_value(ms, "SHLVL=", new_val, get_env_idx(ms->env,
				"SHLVL=") == -1))
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

static char	**env_i_case(t_minishell *ms)
{
	char	**env;
	char	*cwd;
	char	*pwd;

	env = NULL;
	ms->env_start = 1;
	env = matrix_add_front("SHLVL=1", env);
	if (!env)
		return (NULL);
	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (free(cwd), free_split(env), NULL);
	env = matrix_add_front(pwd, env);
	env = matrix_add_front(VAR_PATH, env);
	env = matrix_add_front("OLDPWD", env);
	free(cwd);
	free(pwd);
	return (env);
}
