/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:50:52 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/05 12:54:15 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	long_overflow_check(char *arg, long *arg_n);

/// @brief Exits the program, or not, according to NODE
/// @param ms Overarching Minishell Structure
/// @param node Current exit node to be executed
/// @param pipe_flag if false, writes the exit message
void	exit_built_in(t_minishell *ms, t_tree_node *node, bool pipe_flag)
{
	long	arg_n;

	if (!pipe_flag)
		printf(BLU "exit" DEF "\n");
	arg_n = 0;
	if (!node->right)
		minishell_clean(*ms, ms->exit_status);
	if (long_check(node->right->cont.args[0], &arg_n))
	{
		if (!node->right->cont.args[1])
			minishell_clean(*ms, arg_n);
		else
		{
			ft_printf_fd(2, "exit: too many arguments\n");
			ms->exit_status = 1;
		}
	}
	else
	{
		ft_printf_fd(2, "exit: %s: numeric argument required\n",
			node->right->cont.args[0]);
		minishell_clean(*ms, 2);
	}
}

/// @brief Checks if ARG is a long and stores it in ARG_N
/// @param arg String to be checked
/// @param arg_n Where the number in ARG is to be stored
/// @return 1 if its a long, 0 if not
int	long_check(char *arg, long *arg_n)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(*arg))
		arg++;
	if (*arg == '-' || *arg == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	while (arg[i] && ft_iswhitespace(arg[i]))
		i++;
	if (arg[i])
		return (0);
	if (long_overflow_check(arg, arg_n))
		return (0);
	return (1);
}

/// @brief Verifies if the number in ARG is within the range of a long
/// @param arg String to be checked
/// @param arg_n Where the number in ARG is to be stored
/// @return 1 if there's overflow, 0 when there isn't overflow
static int	long_overflow_check(char *arg, long *arg_n)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*arg == '+' || *arg == '-')
		if (arg++ && *(arg - 1) == '-')
			sign = -1;
	while (ft_isdigit(*arg))
	{
		if (num > LONG_MAX / 10)
			return (1);
		if (num == LONG_MAX / 10 && ((sign == -1 && *arg - '0' > -(LONG_MIN
						% 10)) || (sign == 1 && *arg - '0' > LONG_MAX % 10)))
			return (1);
		num = num * 10 + (*arg - '0');
		arg++;
	}
	*arg_n = num * sign;
	return (0);
}
