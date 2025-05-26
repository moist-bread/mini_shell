
#include "../../Inc/minishell.h"

/// @brief Initializes the values of the Minishell Struct
/// @param minis Overarching Minishell Structure
/// @param env Environment recieved by the program
void	minishell_struct_init(t_minishell *minis, char **env)
{
	init_sigact(minis, 'P');
	minis->tree_head = NULL;
	minis->exit_status = 0;
	minis->env = env_init(minis, env);
	if (!minis->env)
	{
		ft_printf_fd(2, "malloc: failed memory allocation on initialization\n");
		exit(1);
	}
	minis->quote = false; // MY FUNCTION
}

char	**env_init(t_minishell *ms, char **old_env)
{
	char	**env;
	char	*temp;
	char	*pwd;

	env = NULL;
	if (!*old_env)
	{
		ms->env_start = 1;
		env = matrix_add_front("SHLVL=1", env);
		if (!env)
			return (NULL);
		temp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", temp);
		free(temp);
		if (!pwd)
			return (free_split(env), NULL);
		env = matrix_add_front(pwd, env);
		free(pwd);
		if (!env)
			return (NULL);
		env = matrix_add_front(VAR_PATH, env);
		env = matrix_add_front("OLDPWD", env);
	}
	else
	{
		ms->env_start = 0;
		env = matrix_dup_char(old_env);
		if (!env)
			return (NULL);
		// add shlvl++
		temp = get_env("SHLVL=", env);
		if (temp)
			replace_env_value(ms, "SHLVL", ft_itoa(new_atoi(temp)),
				get_env_idx(env, "SHLVL="));
		else
			env = matrix_add_front("SHLVL=1", env);
	}
	return (env);
}

int	new_atoi(char *value)
{
	int	lvl;

	lvl = 1;
	return (lvl);
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
