
#include "../../Inc/minishell.h"

/// @brief Gets the Value associated with Name SEARCH
/// @param search Name for which to search in the existing ENV
/// @param env Environment
/// @return Value corresponding to SEARCH name
char	*get_env(char *search, char **env)
{
	int	i;

	if (!env || !search)
		return (NULL);
	i = find_env(env, search);
	if (i != -1)
		return ((env[i] + ft_strlen(search)));
	return (NULL);
}

int	find_env(char **env, char *search)
{
	int	len;
	int	i;

	if (!env)
		return (-1);
	len = ft_strlen(search);
	printf("find: %s\n", search);
	i = 0;
	while (env[i])
	{
		// printf("name: %s\n", env[i]);
		// printf("end: %c\n", env[i][len]);
		// printf("diff: %d\n", ft_strncmp(env[i], search, len - 1));
		if (search[len - 1] == '=' && !ft_strncmp(env[i], search, len - 1)
			&& (env[i][len - 1] == '=' || !env[i][len - 1]))
			break ;
		if (search[len - 1] != '=' && !ft_strncmp(env[i], search, len)
			&& (env[i][len] == '=' || !env[i][len]))
			break ;
		i++;
	}
	if (env[i])
		return (i);
	return (-1);
}

void	replace_env(char **env, char *name, char *new)
{
	int	old_idx;

	if (!env || !name || !new)
		return ; // explode
	old_idx = find_env(env, name);
	if (old_idx < 0)
		return ;
	free(env[old_idx]);
	env[old_idx] = ft_strdup(new);
	if (!env[old_idx])
		return ; // explode
}

void	export_append(char **env, int old_idx, char *new)
{
	char	*appended;
	int		new_len;
	int		i;
	int		j;

	// do safe guards
	i = 0;
	while (new[i] != '=')
		i++;
	if (!ft_strchr(env[old_idx], '='))
		i--;
	new_len = ft_strlen(&new[i + 1]) + ft_strlen(env[old_idx]);
	appended = ft_calloc(new_len + 1, sizeof(char));
	if (!appended)
		return ; // explode
	j = -1;
	while (env[old_idx][++j])
		appended[j] = env[old_idx][j];
	j--;
	while (j < new_len)
		appended[++j] = new[++i];
	free(env[old_idx]);
	env[old_idx] = appended;
}

/// @brief Adds string ADD to the ENV on index IDX
/// @param env Environment to be added to
/// @param add String to be added to ENV
/// @param idx Index for where to add
/// @param len Length of ENV
/// @return New ENV with added ADD
char	**env_add_to_index(char **env, char *add, size_t idx, size_t len)
{
	char	**new;
	int		i;
	int		j;

	if ((!add && !env) || len < 1 || idx > len)
		return (NULL);
	if (!add || idx > len + 1)
		return (env);
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (env && ++i <= (int)len)
	{
		if (i == (int)idx)
		{
			new[++j] = ft_strdup(add);
			if (!new[j])
				return (free(new), env);
		}
		new[++j] = env[i];
	}
	free(env);
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

	// this function is kinda useless
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
	free(original);
	return (new);
}
