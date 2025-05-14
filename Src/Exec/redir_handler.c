
#include "../../Inc/minishell.h"

static int	here_doc_redir(t_minishell minishell, char *limiter);

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
	char	*line;

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
		here_doc_readline(limiter, here_pipe[1]);
		minishell_clean(minishell, 0);
	}
	waitpid(id, NULL, 0);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

static void	here_doc_readline(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			ft_putendl_fd(line, fd);
			free(line);
		}
		else  // CTRL D CASE
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')",
				limiter); // error
			break ;
		}      
	}
	if (line)
		free(line);
}

/// @brief Recurcivelly checks and opens all redirections associated with NODE
/// @param node Current tree node being checked for redirections
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
void	redir_handler(t_tree_node *node, int *in, int *out)
{
	if (!node->left) // no more redir
		return ;
	if (node->left->type == REDIR_IN) // IN <
	{
		if (*in > 2)
			close(*in);
		*in = open(node->left->cont.file, O_RDONLY);
	}
	else if (node->left->type == REDIR_OUT) // OUT >
	{
		if (*out > 2)
			close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (node->left->type == REDIR_OUT_APPEND) // APPEND OUT >>
	{
		if (*out > 2)
			close(*out);
		*out = open(node->left->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	if (*in == -1 || *out == -1) // failed open
		return (perror(node->left->cont.file));
	if (node->left->left) // more redir
		redir_handler(node->left, in, out);
}
