
#include "../../Inc/minishell.h"

static int	export_validate_options(t_tree_node *node, int *status);
static int	invalid_export(char *arg, int *status);
static void	export_distribute(t_minishell *ms, char *arg, char *key);

/// @brief Prints or Creates variables according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current export node to be executed
void	export_built_in(t_minishell *ms, t_tree_node *node)
{
	char	*key;
	int		i;

	printf(YEL "\nEntering export built in" DEF "\n\n");
	if (!export_validate_options(node->right, &ms->exit_status))
		return ;
	if (!node->right)
		return (print_env(*ms, 1));
	i = -1;
	while (node->right->cont.args[++i])
	{
		printf("export arg[%d]: \"%s\"\n", i, node->right->cont.args[i]);
		if (invalid_export(node->right->cont.args[i], &ms->exit_status))
			continue ;
		key = get_export_key(node->right->cont.args[i]);
		if (!key)
			continue ; // explode ???
		printf("key= %s\n", key);
		export_distribute(ms, node->right->cont.args[i], key);
		if (key)
			free(key);
	}
}

/// @brief Checks if NODE exists and if it's an invalid option or just an argument
/// @param node Possible argument node
/// @param status Exit status to update
/// @return 0 when invalid, 1 when valid
static int	export_validate_options(t_tree_node *node, int *status)
{
	*status = 0;
	if (!node)
		return (1);
	if (node->cont.args[0][0] == '-' && node->cont.args[0][1])
	{
		printf("export: -%c: invalid option\n", node->cont.args[0][1]);
		printf("export: usage: export [name[=value] ...]\n");
		*status = 2;
		return (0);
	}
	return (1);
}

/// @brief Verifies if recieved ARG is an invalid identifier
/// @param arg Identifier
/// @return 1 when invalid, 0 when valid
static int	invalid_export(char *arg, int *status)
{
	int	inv;
	int	i;

	// must begin with a letter or underscore
	// can only contain letters, digits, and underscores
	// depois do = podes ter oque lhe apetecer
	inv = 0;
	if (arg[0] == '_' && arg[1] == '=')
		return (1);
	if (!ft_isalpha(*arg) && *arg != '_')
		inv = 1;
	i = -1;
	while (!inv && arg[++i] && arg[i + 1] != '=')
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			inv = 1;
	if (!inv && arg[i] && !ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
		inv = 1;
	if (inv)
	{
		printf("export: \'%s\': not a valid identifier\n", arg);
		*status = 1;
	}
	return (inv);
}

/// @brief Adds or alters the enviroment variables according to ARG
/// @param ms Overarching Minishell Structure
/// @param arg Current argument being exported
/// @param key Key name present in ARG
static void	export_distribute(t_minishell *ms, char *arg, char *key)
{
	int	env_idx;
	int	env_len;
	int	key_len;

	env_idx = get_env_idx(ms->env, key);
	key_len = ft_strlen(key);
	if (env_idx == -1)
	{
		env_len = (int)ft_matrixlen(ms->env);
		if (ft_strchr(arg, '=')) // key not present (is good)
		{
			printf("key not present (is good)\n");
			if (arg[key_len - 1] == '+')
				ft_memmove(&arg[key_len - 1], &arg[key_len],
					ft_strlen(&arg[key_len - 1]));
			ms->env = matrix_add_to_index(ms->env, arg, env_len, env_len);
		}
		else // key not present (is bad)
		{
			printf("key not present (is bad)\n");
			ms->env = matrix_add_to_index(ms->env, arg, ms->env_start++,
					env_len);
		}
	}
	else if (arg[key_len - 1] == '+')
	{
		printf("key is present, export append\n");
		export_append(ms, env_idx, arg);
	}
	else if (ft_strcmp(ms->env[env_idx], arg) && ft_strchr(arg, '='))
	{
		printf("get env \"%s\"\n", ms->env[env_idx]);
		printf("key is present, different value\n");
		replace_env_value(ms, key, get_export_value(arg), env_idx);
	}
}
