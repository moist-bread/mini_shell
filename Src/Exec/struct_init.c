
#include "../../Inc/minishell.h"

static void	env_init(t_minishell *ms, char **old_env);
static void	create_needed_vars(char ***env, int *env_start);
static int	safe_add_front(char *add, char ***original);

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
static void	env_init(t_minishell *ms, char **old_env)
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
}

/// @brief Checks if the needed variables to start minishell exist
/// , if not, creates them
/// @param env Pointer to the New Environemnt
/// @param env_start Index in the MS struct that indicated valueless vars
static void	create_needed_vars(char ***env, int *env_start)
{
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
		if (!safe_add_front(temp, env))
			return ;
		free(temp);
	}
	temp = get_env("PATH=", *env);
	if (!temp && !safe_add_front(VAR_PATH, env))
		return ;
	temp = get_env("OLDPWD=", *env);
	if (!temp && safe_add_front("OLDPWD", env))
		*env_start = 1;
}

static int	safe_add_front(char *add, char ***original)
{
	char	**new;

	new = matrix_add_front(add, *original);
	if (!new)
	{
		free_split(*original);
		*original = NULL;
		return (0);
	}
	*original = new;
	return (1);
}
