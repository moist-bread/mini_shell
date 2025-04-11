#include "../../Inc/pipex.h"
#include "../../Inc/minishell.h"

void redir_handler(t_minishell minishell, t_tree_node *cmd_node, int *in, int *out)
{
	if (!cmd_node->left) // NO REDIR
		return ;	
	else if (cmd_node->left->type == REDIR_IN) // IN <
	{
		if (*in > 2)
			close(*in);	
		*in = open(cmd_node->left->cont.file, O_RDONLY);
	}
	else if (cmd_node->left->type == REDIR_HERE_DOC) // HERE_DOC IN <<
	{
		if (*in > 2)
			close(*in);
		*in = here_doc_redir(cmd_node->left->cont.file); // do it directly onto a pipe write end
	}
	else if (cmd_node->left->type == REDIR_OUT) // OUT >
	{
		if (*out > 2)
			close(*out);	
		*out = open(cmd_node->left->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else if (cmd_node->left->type == REDIR_OUT_APPEND) // APPEND OUT >>
	{
		if (*out > 2)
			close(*out);	
		*out = open(cmd_node->left->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	if (*in == -1 || *out == -1) // NO MORE REDIRS ARE HANDLED and cmd doesnt execute? the one
		pipex_clean_up(minishell, 1); // write bash: cmd_node->left->cont.file: perror IDK
	if (cmd_node->left->left) // more redir
		redir_handler(minishell, cmd_node->left, in, out);	
}

int	here_doc_redir(char *limiter)
{
	int here_pipe[2];
	char *line;
	
	if(pipe(here_pipe) == -1)
		; // abort
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				break ;
			ft_putstr_fd(line, here_pipe[1]);
			free(line);
		}
		else
			break; // CTRL D CASE write a bunch of stuff about expected limiter
	}
	if (line)
		free(line);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

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
