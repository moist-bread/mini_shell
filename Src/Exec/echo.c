/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:50:44 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/06 17:07:20 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	echo_validate_option(char *arg);

/// @brief Echoes NODES's arguments and handles the option -n
/// @param ms Overarching Minishell Structure
/// @param node Current echo node to be executed
/// @param fd File Descriptor for where to send the output
void	echo_built_in(t_minishell *ms, t_tree_node *node, int fd)
{
	int	n_opt;
	int	i;

	n_opt = 0;
	i = -1;
	while (node->right && node->right->cont.args[++i])
	{
		if (i == 0)
		{
			n_opt = echo_validate_option(node->right->cont.args[i]);
			while (n_opt && node->right->cont.args[++i]
				&& echo_validate_option(node->right->cont.args[i]))
				n_opt++;
		}
		if ((!n_opt && i > n_opt) || (n_opt && i > n_opt))
			ft_printf_fd(fd, " ");
		if (node->right->cont.args[i])
			ft_printf_fd(fd, "%s", node->right->cont.args[i]);
		else
			break ;
	}
	if (!n_opt)
		ft_printf_fd(fd, "\n");
	ms->exit_status = 0;
}

/// @brief Checks if ARG is a valid -n option or just an argument
/// @param arg Possible option argument
/// @return 1 when valid, 0 when invalid
static int	echo_validate_option(char *arg)
{
	int	i;

	if (*arg == '-' && arg[1])
	{
		i = 0;
		while (arg[++i] == 'n')
			;
		if (!arg[i])
			return (1);
	}
	return (0);
}
