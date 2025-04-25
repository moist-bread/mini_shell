
#include "../../Inc/minishell.h"

/// @brief Recurcivelly checks and opens all redirections associated with NODE
/// @param minishell Overarching Minishell Structure
/// @param node Current tree node being checked for redirections
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
void redir_handler(t_minishell minishell, t_tree_node *node, int *in, int *out)
{
	if (!node->left) // NO REDIR
		return ;
	redir_opening(minishell, node->left, in, out);
	if (*in == -1 || *out == -1)
	{
		// NO MORE REDIRS ARE HANDLED, cur cmd doesnt exec?
		perror(node->left->cont.file);
		minishell_clean(minishell, 1);
	}	
	if (node->left->left) // more redir
		redir_handler(minishell, node->left, in, out);	
}

/// @brief Opens files specified by NODE and stores it in IN or OUT,
/// according to the NODE type
/// @param minishell Overarching Minishell Structure
/// @param node Current REDIR node being handled
/// @param in Var where to store input redirections
/// @param out Var where to store output redirections
void redir_opening(t_minishell minishell, t_tree_node *node, int *in, int *out)
{
	if (node->type == REDIR_IN) // IN <
	{
		if (*in > 2)
			close(*in);	
		*in = open(node->cont.file, O_RDONLY);
	}
	else if (node->type == REDIR_HERE_DOC) // HERE_DOC IN <<
	{
		if (*in > 2)
			close(*in);
		*in = here_doc_redir(minishell, node->cont.file);
	}
	else if (node->type == REDIR_OUT) // OUT >
	{
		if (*out > 2)
			close(*out);	
		*out = open(node->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (node->type == REDIR_OUT_APPEND) // APPEND OUT >>
	{
		if (*out > 2)
			close(*out);	
		*out = open(node->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
}

/// @brief Starts a here doc and writes input until LIMITER is written
/// @param minishell Overarching Minishell Structure
/// @param limiter sentence that stops the here_doc
/// @return Read end fd of opened pipe
int	here_doc_redir(t_minishell minishell, char *limiter)
{
	int here_pipe[2];
	char *line;
	
	if(pipe(here_pipe) == -1)
		minishell_clean(minishell, 1); // abort ?
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			ft_putstr_fd(line, here_pipe[1]);
			ft_putstr_fd("\n", here_pipe[1]);
			free(line);
		}
		else // CTRL D CASE 
			break; // write a bunch of stuff about expected limiter
	}
	if (line)
		free(line);
	close(here_pipe[1]);
	return (here_pipe[0]);
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
