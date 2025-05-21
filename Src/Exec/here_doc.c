
#include "../../Inc/minishell.h"

static int	here_doc_redir(t_minishell minishell, char *limiter);
static void	here_doc_readline(t_minishell ms, char *limiter, int fd);

void	multi_here_doc_handler(t_minishell ms, t_pipe_data *pdata)
{
	t_tree_node	*pin;
	int			idx;

	printf(YEL "\n- multiple heredoc" DEF "\n\n");
	pdata->here_docs = ft_calloc(pdata->cmd_n, sizeof(int));
	if (!pdata->here_docs)
		minishell_clean(ms, 1); // fail malloc ABORT?
	pin = ms.tree_head;
	idx = -1;
	while (++idx < pdata->cmd_n)
	{
		single_here_doc_handler(ms, pin, &pdata->here_docs[idx]);
		pin = pin->right;
	}
}

void	single_here_doc_handler(t_minishell ms, t_tree_node *pin, int *in)
{
	t_tree_node	*runner;

	printf(YEL "\n-- single heredoc" DEF "\n\n");
	runner = pin->left;
	while (runner)
	{
		printf("redir node loop_\n");
		if (runner->type == REDIR_HERE_DOC)
			*in = here_doc_redir(ms, runner->cont.limiter);
		else if (runner->type == REDIR_IN)
		{
			if (*in > 2)
				close(*in);
			*in = 0;
		}
		runner = runner->left;
	}
}

/// @brief Starts a here doc and writes input until LIMITER is written
/// @param minishell Overarching Minishell Structure
/// @param limiter sentence that stops the here_doc
/// @return Read end fd of opened pipe
static int	here_doc_redir(t_minishell minishell, char *limiter)
{
	int		here_pipe[2];
	int		id;

	if (pipe(here_pipe) == -1)
		minishell_clean(minishell, 1); // abort ?
	id = fork();
	if (id < 0)
	{
		// maybe return -1 and protect in the single_hd ft
		minishell_clean(minishell, 1); // fail fork abort WITHOUT EXIT
	} 
	if (id == 0)
	{
		here_doc_readline(minishell, limiter, here_pipe[1]);
		minishell_clean(minishell, 0);
	}
	waitpid(id, NULL, 0);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

static void	here_doc_readline(t_minishell ms, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			ft_printf_fd(fd, "%s\n", line);
			free(line);
		}
		else  // CTRL D CASE
		{
			ft_printf_fd(2, "warning: here-document delimited by end-of-file (wanted `%s')\n",
				limiter);
			break ;
		}      
	}
	if (line)
		free(line);
}
