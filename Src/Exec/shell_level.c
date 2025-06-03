
#include "../../Inc/minishell.h"

static int	assign_sh_lvl(char *value);

/// @brief Replaces the old SHLVL value with an updated one
/// @param ms Overarching Minishell Structure
/// @param shl_idx Index that correspondes to the SHLVL variable
/// @return New Environemnt
char	**shell_level_updater(t_minishell *ms, int shl_idx)
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
