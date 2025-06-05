/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:50:34 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 12:04:14 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	invalid_cd(t_tree_node *node, int *status);
static void	cd_update_pwd(t_minishell *ms);

/// @brief Changes directory according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current cd node to be executed
void	cd_built_in(t_minishell *ms, t_tree_node *node)
{
	char	*path;

	if (node->right && invalid_cd(node->right, &ms->exit_status))
		return ;
	if (node->right)
		path = *node->right->cont.args;
	else
		path = get_env("HOME=", &ms->env[ms->env_start]);
	if (!path || chdir(path) == -1)
	{
		ft_printf_fd(2, "cd: ");
		if (!path)
			ft_printf_fd(2, "HOME not set\n");
		else
			perror(path);
		ms->exit_status = 1;
	}
	else
		cd_update_pwd(ms);
}

/// @brief Checks for invalid options or argument amount for cd built in
/// @param node ARG Node associated with a cd BUILT IN Node
/// @param status Exit Status
/// @return 1 when invalid, 0 when valid
static int	invalid_cd(t_tree_node *node, int *status)
{
	if (node->cont.args[0][0] == '-' && node->cont.args[0][1])
	{
		ft_printf_fd(2, "cd: -%c: invalid option\n", node->cont.args[0][1]);
		*status = 2;
		return (1);
	}
	else if (node->cont.args[1])
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		*status = 1;
		return (1);
	}
	return (0);
}

/// @brief Updates values of the variables PWD and OLDPWD in the environment
/// @param ms Overarching Minishell Structure
static void	cd_update_pwd(t_minishell *ms)
{
	int		old_pi;
	int		env_len;
	char	*cur;

	old_pi = get_env_idx("OLDPWD=", ms->env);
	if (old_pi == -1)
	{
		env_len = (int)ft_matrixlen(ms->env);
		if (!safe_add_to_index(&ms->env, "OLDPWD=", env_len, env_len))
			minishell_clean(*ms, 1);
		old_pi = env_len;
	}
	if (replace_env_value(ms, "OLDPWD=", get_env("PWD=", ms->env), old_pi)
		== -1)
		minishell_clean(*ms, 1);
	cur = getcwd(NULL, 0);
	if (replace_env_value(ms, "PWD=", cur, get_env_idx("PWD=", ms->env)) == -1)
		return (free(cur), minishell_clean(*ms, 1));
	if (cur)
		free(cur);
	ms->exit_status = 0;
}

/// @brief 
/// @param og Pointer to original matrix
/// @param add String to be added to OG
/// @param idx Index for where to add
/// @param len Length of OG
/// @return 1 on success (safe), 0 on failure (not safe)
int	safe_add_to_index(char ***og, char *add, size_t idx, size_t len)
{
	char	**new;

	new = matrix_add_to_index(*og, add, idx, len);
	if (!new)
	{
		free_split(*og);
		*og = NULL;
		return (0);
	}
	*og = new;
	return (1);
}

/// @brief Print name of current/working directory
/// @param ms Overarching Minishell Structure
/// @param node Current pwd node to be executed
/// @param fd possible redir file descriptor
void	pwd_built_in(t_minishell *ms, t_tree_node *node, int fd)
{
	char	*pwd;

	if (node->right && *node->right->cont.args[0] == '-'
		&& node->right->cont.args[0][1])
	{
		ft_printf_fd(2, "pwd: -%c: invalid option\n",
			node->right->cont.args[0][1]);
		ft_printf_fd(2, "pwd: usage: pwd\n");
		ms->exit_status = 2;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ms->exit_status = 1;
		else
		{
			ft_printf_fd(fd, "%s\n", pwd);
			free(pwd);
			ms->exit_status = 0;
		}
	}
}
