
#include "../../Inc/minishell.h"

/// @brief Removes Variables from Environment according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current usnet node to be executed
void	unset_built_in(t_minishell *ms, t_tree_node *node)
{
	int	env_idx;
	int	i;

	// printf(YEL "\nEntering unset built in" DEF "\n\n");
	ms->exit_status = 0;
	if (!node->right)
		return ;
	if (node->right->cont.args[0][0] == '-' && node->right->cont.args[0][1])
	{
		ft_printf_fd(2, "unset: -%c: invalid option\n",
			node->right->cont.args[0][1]);
		ft_printf_fd(2, "unset: usage: unset [name ...]\n");
		ms->exit_status = 2;
		return ;
	}
	i = -1;
	while (node->right->cont.args[++i])
	{
		// printf("unset arg[%d]: \"%s\"\n", i, node->right->cont.args[i]);
		env_idx = get_env_idx(node->right->cont.args[i], ms->env);
		if (env_idx != -1)
			remove_env_var(ms, env_idx, ft_matrixlen(ms->env)); // HERE
		else
			continue ;
	}
}

/// @brief Removes variable located at IDX from the Environment
/// @param ms Overarching Minishell Structure
/// @param idx Index of the variable to be removed
/// @param len Length of the Environment
void	remove_env_var(t_minishell *ms, size_t idx, size_t len)
{
	char	**new;
	int		i;
	int		j;

	// printf("remove var(idx: %zu, len: %zu)\n", idx, len);
	if (!ms->env || len < 1 || idx >= len)
		return ;
	new = ft_calloc(len, sizeof(char *));
	if (!new)
		return (error_msg_status("malloc", &ms->exit_status, 1));
	if ((int)idx < ms->env_start)
		ms->env_start--;
	i = -1;
	j = -1;
	while (++i < (int)len)
	{
		if (i == (int)idx)
			free(ms->env[i++]);
		new[++j] = ms->env[i];
	}
	free(ms->env);
	ms->env = new;
}
