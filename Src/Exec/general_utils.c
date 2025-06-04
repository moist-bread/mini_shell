/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:51:13 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 13:31:34 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/// @brief Cleans all content from the MINISHELL struct
/// @param minishell Overarching Minishell Structure
/// @param status Process exit status
void	minishell_clean(t_minishell minishell, int status)
{
	if (minishell.tree_head)
		free_tree(&minishell.tree_head);
	free_split(minishell.env);
	master_close();
	exit(status);
}

/// @brief Waits for the pids in IDS and stores it's exit status in STATUS
/// @param proc_n Amount of processes to wait for
/// @param ids Array containing the ids of said processes
/// @param status Pointer to var where to store the final exit status in
void	process_waiting(int proc_n, int *ids, int *status)
{
	int	i;
	int	signal;
	int	exit_status;

	i = -1;
	*status = 0;
	while (++i < proc_n)
		waitpid(ids[i], &exit_status, 0);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		signal = WTERMSIG(exit_status);
		if (signal == SIGINT)
			printf("\n");
		*status = 128 + signal;
	}
}

/// @brief Closes all non standard file descriptors
void	master_close(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

/// @brief Writes perror with MESSAGE and changed STATUS to VALUE
/// @param message to be sent with perror(), when NULL no message is written
/// @param status pointer to the exit status to alter
/// @param value value to alter it to
void	error_msg_status(char *message, int *status, int value)
{
	*status = value;
	if (message)
		perror(message);
}
