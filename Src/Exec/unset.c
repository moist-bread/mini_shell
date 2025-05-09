
#include "../../Inc/minishell.h"

/// @brief Removes Variables from Environment according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current usnet node to be executed
void	unset_built_in(t_minishell *ms, t_tree_node *node)
{
	int	env_idx;
	int	i;

	printf(YEL "\nEntering unset built in" DEF "\n\n");
	if (!node->right)
		return ;
	i = -1;
	while (node->right->cont.args[++i])
	{
		printf("unset arg[%d]: \"%s\"\n", i, node->right->cont.args[i]);
		env_idx = get_env_idx(ms->env, node->right->cont.args[i]);
		if (env_idx == -1)
			continue ;
		else
			remove_env_var(ms, env_idx, ft_matrixlen(ms->env));
	}
}

void	remove_env_var(t_minishell *ms, size_t idx, size_t len)
{
	char	**new;
	int		i;
	int		j;

	if (!ms->env || len < 1 || idx >= len)
		return ;
	new = ft_calloc(len, sizeof(char *));
	if (!new)
		return ; // explode
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
