
#include "../../Inc/minishell.h"

/// @brief Gets the Value associated with Name SEARCH
/// @param search Name for which to search in the existing ENV
/// @param env Environment
/// @return Value corresponding to SEARCH name
char	*get_env(char *search, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], search, ft_strlen(search)) != 0)
		i++;
	if (env[i]) // find a way to check if its within non export range or nah
		return ((env[i] + ft_strlen(search))); // aka its correctly formated
	return (NULL);
}

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

void export_built_in(t_minishell minishell, t_tree_node *node)
{
	char *name;
	int i;

	if (!node->right)
		print_env(minishell, 1);
	i = -1;
	while (node->right->cont.args[++i])
	{
		name = get_export_name(node->right->cont.args[i]);
		if (!get_env(name, minishell.env))// name not present
		{
			if (correct_export_format(node->right->cont.args[i])) // is good and doesnt exist
				minishell.env = env_add_to_index(minishell.env, node->right->cont.args[i], minishell.env_lim++);
			else // is bad and doesnt exist
				minishell.env = env_add_to_index(minishell.env, node->right->cont.args[i], ft_matrixlen(minishell.env));
		}
		else if (correct_export_format(node->right->cont.args[i]) && \
				strcmp(get_env(name, minishell.env), node->right->cont.args[i] \
				+ ft_strlen(name))) // exists is good and diff
		{
			// CHANGE FOR FT_STRCMP // name exits, value diff
			replace_env(find_env(minishell.env, name), node->right->cont.args[i]);// FIND AND REPLACE
		}
	}	
}

int correct_export_format(char *arg)
{
	if (!arg)
		return(0);
	return (1);
}

char *get_export_name(char *arg)
{
	int i;

	i = -1;
	while (arg[++i] && arg[i] != '=')
		;
	if (arg[i] == '=')
		return (ft_strdup(arg)); // make it ft_strndup
	else
		return (ft_strdup(arg));
}

void print_env(t_minishell minishell, int full_env_flag)
{
	int i;

	i = -1;
	if (full_env_flag)
		while (minishell.env[++i])
			printf("%s\n", minishell.env[i]);
	else
		while (++i <= minishell.env_lim)
			printf("%s\n", minishell.env[i]);
}

char	*find_env(char **env, char *search)
{
	int len;
	int i;

	if (!env)
		return (NULL);
	len = ft_strlen(search);
	i = 0;
	while (env[i] && ft_strncmp(env[i], search, len))
		i++;
	if (env[i])
		return (env[i]);
	return (NULL);
}

void replace_env(char *old, char *new)
{
	free(old);
	old = ft_strdup(new);
	if (!old)
		;//explode

}

/// @brief Adds string ADD to the ENV on index IDX
/// @param env Environment to be added to
/// @param add String to be added to ENV
/// @param idx Index for where to add
/// @return New ENV with added ADD
char **env_add_to_index(char **env, char *add, size_t idx)
{
	char	**new;
	int		i;
	int		j;

	if (!add && !env)
		return (NULL);
	if (!add || idx > ft_matrixlen(env) + 1)
		return (env);
	new = malloc((ft_matrixlen(env) + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (env && env[++i])
	{
		if (i == (int)idx)
		{
			new[++j] = ft_strdup(add);
			if (!new[j])
				return(free(new), env);
		}
		new[++j] = env[i];
	}
	new[++j] = NULL;
	free (env);
	return (new);
}

/// @brief Adds string ADD to the Beggining of matrix ORIGINAL
/// @param add String to be added
/// @param original Original matrix
/// @return New matrix (add + original)
char	**env_add_front(char *add, char **original)
{
	char	**new;
	int		i;

	if (!add && !original)
		return (NULL);
	if (!add)
		return (matrix_dup_char(original));
	new = malloc((ft_matrixlen(original) + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = ft_strdup(add);
	i = -1;
	while (original && original[++i])
	{
		new[i + 1] = original[i];
		if (!new[i + 1])
			free_matrix((void **)new, i + 1);
	}
	if (original)
		new[i + 1] = NULL;
	else
		new[1] = NULL;
	free (original);
	return (new);
}
