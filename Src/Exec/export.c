
#include "../../Inc/minishell.h"

/// @brief Prints or Creates variables according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current export node to be executed
void	export_built_in(t_minishell *ms, t_tree_node *node)
{
	char	*key;
	int		i;

	printf(YEL "\nEntering export built in" DEF "\n\n");
	if (!node->right)
		return (print_env(*ms, 1));
	i = -1;
	while (node->right->cont.args[++i])
	{
		printf("export arg[%d]: \"%s\"\n", i, node->right->cont.args[i]);
		if (invalid_export(node->right->cont.args[i]))
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

/// @brief Prints either export or env according to EXPORT_FLAG
/// @param minishell Overarching Minishell Structure
/// @param export_flag 1 prints export, 0 prints env
void	print_env(t_minishell minishell, int export_flag)
{
	int		i;
	int		j;
	char	**temp;

	i = minishell.env_start;
	if (export_flag)
	{
		temp = sort_matrix(minishell.env, (int)ft_matrixlen(minishell.env));
		i = -1;
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
		while (minishell.env[i])
			printf("%s\n", minishell.env[i++]);
}

/// @brief Verifies if recieved ARG is an invalid identifier
/// @param arg Identifier
/// @return 1 when invalid, 0 when valid
int	invalid_export(char *arg)
{
	int	i;

	// must begin with a letter or underscore
	// can only contain letters, digits, and underscores
	// depois do = podes ter oque lhe apetecer
	if (!ft_isalpha(*arg) && *arg != '_')
		return (printf("export: \'%s\': not a valid identifier\n", arg), 1);
	if (arg[0] == '_' && arg[1] == '=')
		return (1);
	i = -1;
	while (arg[++i] && arg[i + 1] != '=')
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (printf("export: \'%s\': not a valid identifier\n", arg), 1);
	if (arg[i] && !ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
		return (printf("export: \'%s\': not a valid identifier\n", arg), 1);
	return (0);
}

/// @brief Adds or alters the enviroment variables according to ARG
/// @param ms Overarching Minishell Structure
/// @param arg Current argument being exported
/// @param key Key name present in ARG
void	export_distribute(t_minishell *ms, char *arg, char *key)
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
			// strjoin shbang in case of append
			if (arg[key_len - 1] == '+')
				ft_memmove(&arg[key_len - 1], &arg[key_len],
					ft_strlen(&arg[key_len]));
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
	else if (ft_strcmp(get_env(key, ms->env), arg + key_len) && ft_strchr(arg,
			'='))
	{
		printf("key is present, different value\n");
		replace_env_value(ms, key, arg, env_idx);
	}
}
