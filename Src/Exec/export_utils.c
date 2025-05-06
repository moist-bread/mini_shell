
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
		return ; // explode
	j = ft_strlcpy(append, ms->env[idx], ft_strlen(ms->env[idx]) + 1);
	printf("append ogn: %s\n", append);
	i = ft_strlcpy(&append[j], &new[i + 1], ft_strlen(&new[i]));
	printf("append new: %s\n", append);
	if (!ft_strchr(ms->env[idx], '='))
		move_env_var(ms, &idx, (int)ft_matrixlen(ms->env) - 1);
	free(ms->env[idx]);
	ms->env[idx] = append;
}

/// @brief Replaces the old value at env[IDX] with the value in NEW
/// @param ms Overarching Minishell Structure
/// @param key Name of variable to be replaced
/// @param new Contains the new value
/// @param idx  Index of the existing variable whos value will be replaced
void	replace_env_value(t_minishell *ms, char *key, char *new, int idx)
{
	/* 
	// step 1 -- allocation
	// get key len + 1 (for the =)
	// get val len
	// calloc
	char	*new_var;
	int key_len = (key);

	new_var = ft_calloc();
	if (!new_var)
		; // explode
	// step 2 -- pasting
	// copy key
	// put =
	// copy val
	printf("old var: %s\n", ms->env[idx]);

	// j = ft_strlcpy(append, ms->env[idx], ft_strlen(ms->env[idx]) + 1);
	// printf("append ogn: %s\n", append);
	// i = ft_strlcpy(&append[j], &new[i + 1], ft_strlen(&new[i]));

	printf("new var: %s\n", new_var);
	// step 3 -- move if needed 
	// incase of not being previously wrongly declared
	// old idx < ms.env_start
	// move their ass
	if (idx < ms->env_start)
		move_env_var(ms, &idx, (int)ft_matrixlen(ms->env) - 1);
	free(ms->env[idx]);
	ms->env[idx] = new_var; */

	// FIX THIS SHIT BRUV
	// instead of getting the whole new thing get only val????

	// agora ficou a faltar o =
	char	*new_val;

	if (!ms->env || !key || !new || idx < 0)
		return ; // explode
	if (key[ft_strlen(key) - 1] == '=')
		key[ft_strlen(key) - 1] = '\0';
	new_val = ft_strjoin(key, new);
	if (!new_val)
		return ; // explode
	printf("new_val joined: %s\n", new_val);
	if (!ft_strchr(ms->env[idx], '='))
		move_env_var(ms, &idx, (int)ft_matrixlen(ms->env) - 1);
	free(ms->env[idx]);
	ms->env[idx] = new_val;
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
		while (ms->env[*old_idx] && *old_idx < new_idx)
		{
			ms->env[*old_idx] = ms->env[*old_idx + 1];
			(*old_idx)++;
		}
	else
		while (ms->env[*old_idx] && *old_idx > new_idx)
		{
			ms->env[*old_idx] = ms->env[*old_idx - 1];
			(*old_idx)--;
		}
	ms->env[*old_idx] = temp;
}
