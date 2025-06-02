
#include "../../Inc/minishell.h"

/// @brief Appends the value contained in NEW to env[IDX]
/// @param ms Overarching Minishell Structure
/// @param idx Index of the existing variable to append to
/// @param new Contains new value to be appended
void	export_append(t_minishell *ms, int idx, char *new)
{
	char	*append;
	int		i;
	int		j;

	if (!new || !ms->env)
		return ;
	i = env_elem_len(new, 1) + 1;
	if (!ft_strchr(ms->env[idx], '='))
		i--;
	append = ft_calloc(ft_strlen(ms->env[idx]) + ft_strlen(&new[i + 1]) + 1,
			sizeof(char));
	if (!append)
		return (error_msg_status("malloc", &ms->exit_status, 1));
	j = ft_strlcpy(append, ms->env[idx], ft_strlen(ms->env[idx]) + 1);
	// printf("original: %s\n", append);
	i = ft_strlcpy(&append[j], &new[i + 1], ft_strlen(&new[i]));
	// printf("appended: %s\n", append);
	if (!ft_strchr(ms->env[idx], '='))
		move_env_var(ms, &idx, (int)ft_matrixlen(ms->env) - 1);
	free(ms->env[idx]);
	ms->env[idx] = append;
	ms->exit_status = 0;
}

/// @brief Replaces the old value at ms->env[IDX] with the NEW value
/// @param ms Overarching Minishell Structure
/// @param key Name of variable to be replaced
/// @param new The new Value to replace it with
/// @param idx  Index of the existing variable
int	replace_env_value(t_minishell *ms, char *key, char *new, int idx)
{
	int		j;
	int		key_len;
	int		new_val_len;
	char	*new_var;

	if (!ms->env || !*key || !new || idx < 0)
		return (1);
	key_len = env_elem_len(key, 1);
	new_val_len = ft_strlen(new) + 2;
	new_var = ft_calloc(key_len + new_val_len, sizeof(char));
	if (!new_var)
		return (perror("malloc"), -1);
	j = ft_strlcpy(new_var, key, key_len + 1);
	new_var[j - 1] = '=';
	// printf("copied key: %s\n", new_var);
	ft_strlcpy(&new_var[j], new, new_val_len);
	// printf("copied new val: %s\n", new_var);
	if (idx < ms->env_start)
		move_env_var(ms, &idx, (int)ft_matrixlen(ms->env) - 1);
	free(ms->env[idx]);
	ms->env[idx] = new_var;
	return (0);
}

/// @brief Moves env and alters the env_start according to OLD_IDX and NEW_IDX
/// @param ms Overarching Minishell Structure
/// @param old_idx Current Index
/// @param new_idx Desired Index
void	move_env_var(t_minishell *ms, int *old_idx, int new_idx)
{
	char	*temp;

	if (!ms->env || *old_idx == new_idx)
		return ;
	if (ms->env_start > *old_idx && ms->env_start <= new_idx)
		ms->env_start--;
	else if (ms->env_start <= *old_idx && ms->env_start > new_idx)
		ms->env_start++;
	temp = ms->env[*old_idx];
	if (*old_idx < new_idx)
	{
		while (ms->env[(*old_idx)++] && *old_idx <= new_idx)
			ms->env[*old_idx - 1] = ms->env[*old_idx];
		(*old_idx)--;
	}
	else
	{
		while (ms->env[(*old_idx)--] && *old_idx >= new_idx)
			ms->env[*old_idx + 1] = ms->env[*old_idx];
		(*old_idx)++;
	}
	ms->env[*old_idx] = temp;
}
