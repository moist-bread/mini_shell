/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:52:20 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 14:56:22 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static void	ambiguous_redir_verify(t_tree_node *node, int *in, int *out);

/// @brief Opens all redirections associated with NODE and
/// stores them in IN and OUT
/// @param ms Overarching Minishell Structure
/// @param node Node from which to check for redirections
/// @param in Variable to store the resulting infile fd
/// @param out Variable to store the resulting outfile fd
/// @return -1 on failure, 0 on success
int	cmd_redir_executer(t_minishell *ms, t_tree_node *node, int *in, int *out)
{
	int	hd;

	hd = 0;
	*in = 0;
	*out = 1;
	single_here_doc_handler(*ms, node, &hd);
	if (hd < 0)
	{
		if (hd == -1)
			ms->exit_status = 1;
		else if (hd == -2)
			ms->exit_status = 130;
		return (-1);
	}
	redir_handler(ms, node, in, out);
	return (successful_redir_check(in, out, hd));
}

/// @brief Recurcivelly checks and opens all redirections associated with NODE
/// @param node Current tree node being checked for redirections
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
void	redir_handler(t_minishell *ms, t_tree_node *node, int *in, int *out)
{
	if (!node->left || (node->left->type != RED_HD && !node->left->cont.file))
		return (ambiguous_redir_verify(node, in, out));
	if (node->left->type == RED_IN)
	{
		safe_close(*in);
		*in = open(node->left->cont.file, O_RDONLY);
	}
	else if (node->left->type == RED_OUT)
	{
		safe_close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (node->left->type == RED_APP)
	{
		safe_close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	if (*in == -1 || *out == -1)
		return (error_msg_status(node->left->cont.file, &ms->exit_status, 1));
	if (node->left->left)
		redir_handler(ms, node->left, in, out);
}

/// @brief Checks for ambiguous (null) redirections and replaces the fd with -1
/// @param node Current tree node being checked for redirections
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
static void	ambiguous_redir_verify(t_tree_node *node, int *in, int *out)
{
	if (!node->left)
		return ;
	if (node->left->type == RED_IN)
	{
		ft_printf_fd(2, "ambiguous redirect\n");
		mem_save(NULL)->exit_status = 1;
		safe_close(*in);
		*in = -1;
	}
	else if (node->left->type == RED_OUT || node->left->type == RED_APP)
	{
		ft_printf_fd(2, "ambiguous redirect\n");
		mem_save(NULL)->exit_status = 1;
		safe_close(*out);
		*out = -1;
	}
}

/// @brief Checks for failure in opened redirs and
/// replaces IN with HD when needed
/// @param in Var where the input redirection is stored
/// @param out Var where the output redirection is stored
/// @param hd Var where the here doc redirection is stored
/// @return 0 on sucess, -1 when there was a failure in opening IN or OUT
int	successful_redir_check(int *in, int *out, int hd)
{
	if (*in == -1 || *out == -1)
	{
		safe_close(*in);
		safe_close(*out);
		return (-1);
	}
	if (hd > 2)
	{
		safe_close(*in);
		*in = hd;
	}
	return (0);
}

/// @brief Closes FD if it is bigger than 2
/// @param fd File descriptor to close
void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}
