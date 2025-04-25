
#include "../../Inc/minishell.h"

// pov someone uses export 
// step 1: check if its well formated
// step 2: if good format, check if NAME already exists 
// 		   if yes, if diff replace value, else nothing, else no add to good place
//					(replace_env / nothing/ env_add_to_index)
// step 3: if bad format check if string already exists
//		   if yes, do nothing, else add to bad place (env_add_to_index)
//					(nothing / env_add_to_index)

// STEP 1: -- get name
// STEP 2: -- check if it already exists
// STEP 3: -- if exists and bad format NOTHING
// STEP 4: -- if exists and good format compare content
// STEP 5: -- if same content NOTHING
// STEP 6: -- if diff content REPLACE

// bro faz um por cada argumento...

// export BANANAAAA - add to index matrix len
// export BANANAAAA - nothing
// export ARG=BOMDIA - add to index env lim
// export ARG=MAUDIA - find and replace
// export .= - invalid


void export_built_in(t_minishell *minishell, t_tree_node *node)
{
	char *name;
	int i;

	printf("\nEntering export built in\n");
	if (!node->right)
		return(print_env(*minishell, 1));
	i = -1;
	while (node->right->cont.args[++i])
	{
		printf("doing arg %d, \"%s\"\n", i, node->right->cont.args[i]);
		name = get_export_name(node->right->cont.args[i]);
		printf("name= %s\n", name);
		if (!name)
			; //explode
		else if (invalid_export(node->right->cont.args[i]))
			invalid_export_message(node->right->cont.args[i]);
		else if (!get_env(name, minishell->env))// name not present
		{
			printf("name not present\n");
			if (correct_export_format(node->right->cont.args[i])) // is good and doesnt exist
			{
				printf("is good\n");
				minishell->env = env_add_to_index(minishell->env, node->right->cont.args[i], ++minishell->env_lim, ft_matrixlen(minishell->env));
			}
			else // is bad and doesnt exist
			{
				printf("is bad\n");
				minishell->env = env_add_to_index(minishell->env, node->right->cont.args[i], ft_matrixlen(minishell->env), ft_matrixlen(minishell->env));
			}
		}
		else if (node->right->cont.args[i][ft_strlen(name) - 1] == '+') // is adittion
		{
			printf("name is present, export append\n");
			export_append(minishell->env, find_env(minishell->env, name), node->right->cont.args[i]);
		}
		else if (ft_strcmp(get_env(name, minishell->env), node->right->cont.args[i] + ft_strlen(name)))
		{
			printf("name is present but is diff value\n");
			// name exits, value diff (find and replace)
			replace_env(minishell->env, find_env(minishell->env, name), node->right->cont.args[i]);
		}
		free(name);
	}	
}

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

/// @brief Verifies if recieved ARG is an invalid export
/// @param arg 
/// @return 
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

void invalid_export_message(char *arg)
{
	if (arg[0] == '_' && arg[1] == '=')
		return ;
	else
		printf("export: \'%s\': not a valid identifier\n", arg);
}

int correct_export_format(char *arg)
{
	if (!arg || !ft_strchr(arg, '='))
		return(0);
	return (1);
}
