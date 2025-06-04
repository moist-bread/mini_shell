/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:49:25 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 14:57:53 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	export_validate_options(t_tree_node *node, int *status);
static int	invalid_export(char *arg, int *status);
static void	export_distribute(t_minishell *ms, char *arg, char *key,
				int env_idx);

/// @brief Prints or Creates variables according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current export node to be executed
/// @param fd possible redir file descriptor
void	export_built_in(t_minishell *ms, t_tree_node *node, int fd)
{
	char	*key;
	int		i;

	if (!export_validate_options(node->right, &ms->exit_status))
		return ;
	ms->exit_status = 0;
	if (!node->right)
		return (print_env(*ms, 1, fd));
	i = -1;
	while (node->right->cont.args[++i])
	{
		if (invalid_export(node->right->cont.args[i], &ms->exit_status))
			continue ;
		key = get_export_key(node->right->cont.args[i]);
		if (!key)
			return (perror("malloc"), minishell_clean(*ms, 1));
		export_distribute(ms, node->right->cont.args[i], key, get_env_idx(key,
				ms->env));
		free(key);
	}
}

/// @brief Checks if NODE exists, if it's an invalid option or an argument
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
		ft_printf_fd(2, "export: -%c: invalid option\n", node->cont.args[0][1]);
		ft_printf_fd(2, "export: usage: export [name[=value] ...]\n");
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
		ft_printf_fd(2, "export: \'%s\': not a valid identifier\n", arg);
		*status = 1;
	}
	return (inv);
}

/// @brief Adds or alters the enviroment variables according to ARG
/// @param ms Overarching Minishell Structure
/// @param arg Current argument being exported
/// @param key Key name present in ARG
/// @param env_idx Index of the variable corresponding to KEY in env
static void	export_distribute(t_minishell *ms, char *arg, char *key,
		int env_idx)
{
	int	env_len;
	int	key_len;

	key_len = ft_strlen(key);
	if (env_idx == -1)
	{
		env_len = (int)ft_matrixlen(ms->env);
		if (ft_strchr(arg, '='))
		{
			if (arg[key_len - 1] == '+')
				ft_memmove(&arg[key_len - 1], &arg[key_len],
					ft_strlen(&arg[key_len - 1]));
			if (!safe_add_to_index(&ms->env, arg, env_len, env_len))
				minishell_clean(*ms, 1);
		}
		else if (!safe_add_to_index(&ms->env, arg, ms->env_start++, env_len))
			minishell_clean(*ms, 1);
	}
	else if (arg[key_len - 1] == '+')
		export_append(ms, env_idx, arg);
	else if (ft_strcmp(ms->env[env_idx], arg) && ft_strchr(arg, '=')
		&& replace_env_value(ms, key, get_export_value(arg), env_idx) == -1)
		minishell_clean(*ms, 1);
}
