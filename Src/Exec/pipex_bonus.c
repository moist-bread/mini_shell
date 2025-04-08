/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:58 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/08 18:42:39 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

typedef enum s_pipe_ms
{
	MALLOC_FAIL, // texto
}		t_pipe_ms;

void	pipex_proc(t_minishell minishell, t_tree_node *tree_head,
			t_pipe_data *pipex);

int	main(int ac, char **av, char **env)
{
	t_pipex_b	pipex_b;
	int			i;

	i = 0;
	if (ac < 5)
		return (master_close(), ft_printf("Wrong Argument Count\n"));
	ft_bzero((void *)&pipex_b, sizeof(t_pipex));
	pipex_b.env = env;
	if_here_doc(&pipex_b, av, ac, &i);
	while (++i < ac - 2)
		loop_pipes(&pipex_b, av, &i);
	the_output(&pipex_b, av, i);
	close(0);
	master_close();
	wait_pid_loop(&pipex_b);
	unlink("here_doc");
	if (WIFEXITED(pipex_b.status))
		return (free(pipex_b.pid), WEXITSTATUS(pipex_b.status));
	return (free(pipex_b.pid), pipex_b.status);
}

void	pipex_proc(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex)
{
	// duplicate but with built in or add to the if
	if (tree_head->left && tree_head->left->type == CMD)
		execute_pipex_cmd(minishell, tree_head->left, pipex);
	if (tree_head->right && tree_head->right->type == CMD)
		execute_pipex_cmd(minishell, tree_head->right, pipex);
	else if (tree_head->right && tree_head->right->type == PIPE)
		pipex_proc(minishell, tree_head->right, pipex);
	multi_proc_wait(pipex, &minishell.exit_status);
	pipex_clean_up();
}

int	execute_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node,
		t_pipe_data *pipex)
{
	// handle redirs + create pipe --
	int	inf;
	int	outf;
	int new_pipe[2];

	if (!cmd_node->left) // NO REDIR
	{
		inf = 0;
		outf = 1;
	}
	else if (cmd_node->left->type == REDIR_IN) // IN <
		inf = open(cmd_node->left->cont.file, O_RDONLY);
	else if (cmd_node->left->type == REDIR_HERE_DOC) // HERE_DOC IN <<
		inf = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644); // do to di pipe!!!
	else if (cmd_node->left->type == REDIR_OUT) // OUT >
		outf = open(cmd_node->left->cont.file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (cmd_node->left->type == REDIR_OUT_APPEND) // APPEND OUT >>
		outf = open(cmd_node->left->cont.file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (outf == -1)
		pipex_clean_up(); // outf didnt open
	// add a verify for -1 when here_doc
	if (pipe(new_pipe) == -1)
		pipex_clean_up(); // pipe didnt create
	pipex->cur_pipe[0] = inf; 
	pipex->cur_pipe[1] = new_pipe[1];
	pipex->next_pipe[0] = new_pipe[0];
	// --

	
	
}

void	pipex_clean_up(void)
{
	;
}