
#include "../../Inc/minishell.h"

/// @brief Gets the Value associated with Key SEARCH
/// @param search Key Name for which to search in ENV
/// @param env Environment
/// @return Value corresponding to the SEARCH key name
char	*get_env(char *search, char **env)
{
	int	i;

	if (!env || !search)
		return (NULL);
	i = get_env_idx(search, env);
	if (i != -1)
		return ((env[i] + ft_strlen(search)));
	return (NULL);
}

/// @brief Gets the index associated with Key SEARCH
/// @param search  Key Name for which to search in ENV
/// @param env Environment
/// @return Index where the SEARCH key name was found
int	get_env_idx(char *search, char **env)
{
	int	len;
	int	i;

	if (!env || !search)
		return (-1);
	len = ft_strlen(search);
	i = -1;
	while (env[++i])
	{
		if (search[len - 1] == '=' && !ft_strncmp(env[i], search, len - 1)
			&& (env[i][len - 1] == '=' || !env[i][len - 1]))
			break ;
		if (search[len - 1] != '=' && !ft_strncmp(env[i], search, len)
			&& (env[i][len] == '=' || !env[i][len]))
			break ;
	}
	if (env[i])
		return (i);
	return (-1);
}

/// @brief Extracts the Key Identifier from ARG
/// @return Identifier Name
char	*get_export_key(char *arg)
{
	int		i;
	char	*name;

	i = env_elem_len(arg, 1);
	if (arg[i] == '=' || arg[i] == '+')
	{
		name = ft_strndup(arg, i + 1);
		if (!name)
			return (NULL);
		if (arg[i] == '+')
			name[i] = '=';
		return (name);
	}
	else
		return (ft_strdup(arg));
}

/// @brief Extracts the Value from ARG
/// @return Identifier Name
char	*get_export_value(char *arg)
{
	int	i;

	i = env_elem_len(arg, 1) + 1;
	if (arg[i] == '=')
		i++;
	return (&arg[i]);
}

/// @brief Sees len of key until '=' or '+', or len of value from there on
/// @param arg Argument from which to exctract len
/// @param key_flag 1 for key, 0 for value
/// @return length of element
int	env_elem_len(char *arg, int key_flag)
{
	int	key;
	int	value;

	key = 0;
	while (arg[key] && arg[key] != '=' && arg[key] != '+')
		key++;
	if (key_flag)
		return (key);
	if (arg[key] && arg[key] != '=')
		key++;
	value = 0;
	while (arg[key + value])
		value++;
	return (value);
}
