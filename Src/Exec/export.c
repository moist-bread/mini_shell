
#include "../../Inc/minishell.h"

// export BANANAAAA - add to index matrix len
// export BANANAAAA - nothing
// export ARG=BOMDIA - add to index env lim
// export ARG=MAUDIA - find and replace
// export ARG+=AQUELEDIA - find and append
// export 6*&^@#.= - invalid
// export BANANAAAA=CONT - find, move and replace

// make all names have an = at the end with or without val
// but when printing if theres no val after = it doesnt print anyhting 

// if it had a value and you try an incorrectly formatted
// it doesnt change the value?!?!?!?1?1?!?!?

/// @brief Prints or Creates variables according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current export node to be executed
void export_built_in(t_minishell *ms, t_tree_node *node)
{
	char *name;
	int i;

	printf("\nEntering export built in\n");
	if (!node->right)
		return(print_env(*ms, 1));
	i = -1;
	while (node->right->cont.args[++i])
	{
		printf("doing arg %d, \"%s\"\n", i, node->right->cont.args[i]);
		name = get_export_name(node->right->cont.args[i]);
		printf("name= %s\n", name);
		if (invalid_export(node->right->cont.args[i]))
			invalid_export_message(node->right->cont.args[i]);
		else if (!name)
			; //explode
		else if (find_env(ms->env, name) == -1)// name not present
		{
			printf("name not present\n");
			if (ft_strchr(node->right->cont.args[i], '=')) // is good and doesnt exist
			{
				printf("is good\n");
				ms->env = env_add_to_index(ms->env, node->right->cont.args[i], ++ms->env_lim, ft_matrixlen(ms->env));
			}
			else // is bad and doesnt exist
			{
				printf("is bad\n");
				ms->env = env_add_to_index(ms->env, node->right->cont.args[i], ft_matrixlen(ms->env), ft_matrixlen(ms->env));
			}
		}
		else if (node->right->cont.args[i][ft_strlen(name) - 1] == '+') // is adittion
		{
			printf("name is present, export append\n");
			export_append(ms->env, find_env(ms->env, name), node->right->cont.args[i]);
		}
		else if (ft_strcmp(get_env(name, ms->env), node->right->cont.args[i] + ft_strlen(name)))
		{
			printf("name is present but is diff value\n");
			// name exits, value diff (find and replace)
			replace_env(ms->env, name, node->right->cont.args[i]);
		}
		if (name)
			free(name);
	}	
}

/// @brief Prints valid env
/// @param minishell 
/// @param full_env_flag 
void print_env(t_minishell minishell, int full_env_flag)
{
	int i;
	int j;
	char **temp;

	i = -1;
	if (full_env_flag)
	{
		temp = sort_matrix(minishell.env, (int)ft_matrixlen(minishell.env));
		while (temp[++i])
		{
			j = 0;
			printf("declare -x ");
			while (temp[i][j] && temp[i][j] != '=')
				printf("%c", temp[i][j++]);
			if (temp[i][j] == '=')
				printf("%c\"%s\"", temp[i][j],  &temp[i][j + 1]);
			printf("\n");
		}
		free(temp);
	}
	else
		while (++i <= minishell.env_lim)
			printf("%s\n", minishell.env[i]);
}

/// @brief Extracts the Identifier from ARG
/// @return Identifier Name
char *get_export_name(char *arg)
{
	int i;
	char *name;

	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	if (arg[i] == '=' || arg[i] == '+')
	{
		name = ft_strndup(arg, i + 1);
		if (arg[i] == '+')
			name[i] = '=';
		return (name);
	}
	else
		return (ft_strdup(arg));
}

/// @brief Verifies if recieved ARG is an invalid identifier
/// @param arg Identifier
/// @return 1 when invalid, 0 when valid
int invalid_export(char *arg)
{
	int i;

	// must begin with a letter or underscore
	// can only contain letters, digits, and underscores
	// depois do = podes ter oque te apetecer
	if (!ft_isalpha(*arg) && *arg != '_')
		return(1);
	if (arg[0] == '_' && arg[1] == '=')
		return(1);
	i = -1;
	while(arg[++i] && arg[i + 1] != '=')
		if(!ft_isalnum(arg[i]) && arg[i] != '_')
			return(1);
	if(arg[i] && !ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+' )
		return(1);
	return (0);
}

/// @brief Writes an error message in case of invalid export 
void invalid_export_message(char *arg)
{
	if (arg[0] == '_' && arg[1] == '=')
		return ;
	else
		printf("export: \'%s\': not a valid identifier\n", arg);
}
