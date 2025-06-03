
#include "../../Inc/minishell.h"

static void env_init(t_minishell *ms, char **old_env);
static char	**shell_level_updater(t_minishell *ms, int shl_idx);
static int	assign_sh_lvl(char *value);
static void	create_needed_vars(char ***env, int *env_start);

/// @brief Initializes the values of the Minishell Struct
/// @param ms Overarching Minishell Structure
/// @param env Environment recieved by the program
void	minishell_struct_init(t_minishell *ms, char **env)
{
	init_sigact(ms, 'P');
	ms->tree_head = NULL;
	ms->exit_status = 0;
	ms->env_start = 0;
	ms->env = NULL;
	env_init(ms, env);
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
static void env_init(t_minishell *ms, char **old_env)
{
	char	**tmp;
	int		sh_lvl;

	if (*old_env)
	{
		ms->env = matrix_dup_char(old_env);
		if (!ms->env)
			return ;
	}
	sh_lvl = get_env_idx("SHLVL=", ms->env);
	if (sh_lvl != -1)
		tmp = shell_level_updater(ms, sh_lvl);
	else
		tmp = matrix_add_front("SHLVL=1", ms->env);
	if (!tmp && ms->env)
		free_split(ms->env);
	ms->env = tmp;
	create_needed_vars(&ms->env, &ms->env_start);
	if (!ms->env)
		return ;
}

/// @brief Replaces the old SHLVL value with an updated one
/// @param ms Overarching Minishell Structure
/// @param shl_idx Index that correspondes to the SHLVL variable
/// @return New Environemnt
static char	**shell_level_updater(t_minishell *ms, int shl_idx)
{
	char	*new_val;

	new_val = ft_itoa(assign_sh_lvl(ms->env[shl_idx] + 6));
	if (!new_val)
		return (NULL);
	if (replace_env_value(ms, "SHLVL=", new_val, shl_idx) == -1)
		return (free(new_val), NULL);
	free(new_val);
	return (ms->env);
}

/// @brief Assigns the New Shell Level based on the previous one
/// @param value Value of the previous shel level
/// @return New Shell Level
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

/// @brief Checks if the needed variables to start minishell exist
/// , if not, creates them
/// @param env Pointer to the New Environemnt
/// @param env_start Index in the MS struct that indicated valueless vars
/// @return 0 on success, -1 on failure
static void	create_needed_vars(char ***env, int *env_start)
{
	char	**new_env;
	char	*temp;
	char	*cwd;

	if (!*env)
		return ;
	temp = get_env("PWD=", *env);
	if (!temp)
	{
		cwd = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", cwd);
		free(cwd);
		new_env = matrix_add_front(temp, *env);
		if (!new_env)
			return (free_split(*env));
		*env = new_env;
		free(temp);
	}
	temp = get_env("PATH=", *env);
	if (!temp)
	{
		new_env = matrix_add_front(VAR_PATH, *env);
		if (!new_env)
			return (free_split(*env));
		*env = new_env;
	}
	temp = get_env("OLDPWD=", *env);
	if (!temp)
	{
		new_env = matrix_add_front("OLDPWD", *env);
		if (!new_env)
			return (free_split(*env), -1);
		*env = new_env;
		*env_start = 1;
	}
	return (0);
}

// SMALL FT TO DO THE MATRIX ADD FRONT AND VERIFY SHIT