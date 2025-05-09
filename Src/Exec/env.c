
#include "../../Inc/minishell.h"

/// @brief Prints the current Environment
/// @param ms Overarching Minishell Structure
/// @param node Current env node to be executed
void	env_built_in(t_minishell *ms, t_tree_node *node)
{
	printf(YEL "\nEntering env built in" DEF "\n\n");
	if (node->right)
	{
		if (node->right->cont.args[0][0] == '-' && node->right->cont.args[0][1])
		{
			ms->exit_status = 125;
			printf("env: invalid option -- \'%c\'\n",
				node->right->cont.args[0][1]);
		}
		else
		{
			ms->exit_status = 127;
			printf("env: \'%s\': No such file or directory\n",
				node->right->cont.args[0]);
		}
		return ;
	}
	ms->exit_status = 0;
	print_env(*ms, 0);
}

/// @brief Prints either export or env according to EXPORT_FLAG
/// @param minishell Overarching Minishell Structure
/// @param export_flag 1 prints export, 0 prints env
void	print_env(t_minishell minishell, int export_flag)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	if (export_flag)
	{
		temp = sort_matrix(minishell.env, (int)ft_matrixlen(minishell.env));
		if (!temp)
			return ; // explode ??
		while (temp[++i])
		{
			j = 0;
			printf("declare -x ");
			while (temp[i][j] && temp[i][j] != '=')
				printf("%c", temp[i][j++]);
			if (temp[i][j] == '=')
				printf("%c\"%s\"", temp[i][j], &temp[i][j + 1]);
			printf("\n");
		}
		free(temp);
	}
	else
		while (minishell.env[++i + minishell.env_start])
			printf("%s\n", minishell.env[i + minishell.env_start]);
}
