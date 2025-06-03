
#include "../../Inc/minishell.h"

static int	here_doc_redir(t_minishell ms, char *lim, bool exp_flag);
static void	here_doc_readline(t_minishell ms, char *limiter, int fd,
				bool exp_flag);

/// @brief Executes all here docs in a PIPE tree and stores the fds in PDATA
/// @param ms Overarching Minishell Structure
/// @param pdata Struct used for the execution of pipes
void	multi_here_doc_handler(t_minishell ms, t_pipe_data *pdata)
{
	t_tree_node	*pin;
	int			idx;

	pin = ms.tree_head;
	idx = -1;
	while (++idx < pdata->cmd_n)
	{
		single_here_doc_handler(ms, pin, &pdata->here_docs[idx]);
		if (pdata->here_docs[idx] == -1)
			minishell_clean(ms, 1);
		if (pdata->here_docs[idx] == -2)
			minishell_clean(ms, 130);
		pin = pin->right;
	}
	init_sigact(&ms, 'I');
}

/// @brief Executes all here docs associated with PIN and stores the last in IN
/// @param ms Overarching Minishell Structure
/// @param pin Current node to be scanned for RED_HD
/// @param in Variable to store the resulting fd
void	single_here_doc_handler(t_minishell ms, t_tree_node *pin, int *in)
{
	t_tree_node	*runner;

	runner = pin->left;
	while (runner && *in > -1)
	{
		if (runner->type == RED_HD)
		{
			init_sigact(&ms, 'I');
			*in = here_doc_redir(ms, runner->cont.limiter, runner->cont.quote);
		}
		else if (runner->type == RED_IN)
		{
			safe_close(*in);
			*in = 0;
		}
		runner = runner->left;
	}
}

/// @brief Opens a pipe and forks for the Here Doc to take place
/// @param ms Overarching Minishell Structure
/// @param lim Limiter String that stops the here_doc
/// @param exp_flag Flag that indicates if the content is to be expanded
/// @return Read end fd of opened pipe, -1 on error, -2 on signal end
static int	here_doc_redir(t_minishell ms, char *lim, bool exp_flag)
{
	int	here_pipe[2];
	int	exit_status;
	int	id;

	exit_status = 0;
	if (pipe(here_pipe) == -1)
		return (perror("pipe"), -1);
	id = fork();
	if (id < 0)
		return (perror("fork"), -1);
	if (id == 0)
	{
		init_sigact(&ms, 'H');
		here_doc_readline(ms, lim, here_pipe[1], exp_flag);
		minishell_clean(ms, 0);
	}
	waitpid(id, &exit_status, 0);
	init_sigact(&ms, 'P');
	close(here_pipe[1]);
	if (exit_status != 0)
		return (close(here_pipe[0]), -2);
	return (here_pipe[0]);
}

/// @brief Starts a readline and writes the input in FD until LIM is written
/// @param lim Limiter string that stops the readline
/// @param fd Write end of a pipe to write to
/// @param exp_flag Flag that indicates if the content is to be expanded
static void	here_doc_readline(t_minishell ms, char *lim, int fd, bool exp_flag)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strcmp(line, lim))
				break ;
			line = my_function(ms, line, exp_flag);
			if (!line)
				break ; // Your malloc exit;
			ft_printf_fd(fd, "%s\n", line);
			free(line);
		}
		else // CTRL D CASE
		{
			ft_printf_fd(2, M_HERE_EOF "(wanted `%s')\n", lim);
			break ;
		}
	}
	if (line)
		free(line);
}
