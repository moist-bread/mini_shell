
#include "../../Inc/minishell.h"

/// @brief Initializes the values of the Minishell Struct
/// @param minis Overarching Minishell Structure
/// @param env Environment recieved by the program
void	minishell_struct_init(t_minishell *minis, char **env)
{
	init_sigact(minis, 'P');
	minis->tree_head = NULL;
	minis->env = matrix_dup_char(env); // needs proper env
	if (!minis->env)
	{
		ft_printf_fd(2, "malloc: failed memory allocation on initialization\n");
		exit(1);
	}
	minis->env_start = 0;
	minis->exit_status = 0;
	minis->quote = false;
}

/// @brief Cleans all content from the MINISHELL struct
/// @param minishell Overarching Minishell Structure
/// @param status Process exit status
void	minishell_clean(t_minishell minishell, int status)
{
	printf("exiting with: %d\n", status);
	if (minishell.tree_head)
		free_tree(minishell.tree_head);
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
