/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:58 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/10 18:14:47 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

typedef enum s_pipe_ms
{
	MALLOC_FAIL, // texto
}		t_pipe_ms;

void	pipex_proc(t_minishell minishell, t_tree_node *tree_head,
		t_pipe_data *pipex, int idx);

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
		t_pipe_data *pipex, int idx)
{
	// duplicate but with built in or add to the if
	if (tree_head->left && tree_head->left->type == CMD)
		execute_pipex_cmd(minishell, tree_head->left, pipex, idx++);
	if (tree_head->right && tree_head->right->type == CMD)
		execute_pipex_cmd(minishell, tree_head->right, pipex, idx++);
	else if (tree_head->right && tree_head->right->type == PIPE)
		pipex_proc(minishell, tree_head->right, pipex, idx);
	multi_proc_wait(pipex, &minishell.exit_status);
	pipex_clean_up();
}

int	execute_pipex_cmd(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx)
{
	// EXECUTE THE COMMAND
	
	// step 1: check redir and open needed --
	int	redir_fd[2];
	ft_bzero(redir_fd, 2);
	redir_handler(minishell, cmd_node, &redir_fd[0], &redir_fd[1]);	
	// --
	
	// step 2: create pipe and assign fds --
	assign_pipe_fds(minishell, pipex, redir_fd, idx); // needs to know if its the last cmd
	// --

	// step 3: fork, parse, dup execute --
	pipex->pid[idx] = fork();
	if (pipex->pid[idx] < 0)
		pipex_clean_up(); // fail fork abort
	if (pipex->pid[idx] == 0)
		child_parse_and_exe(minishell, cmd_node, pipex, idx);
	// --
	
	// step 4: parent close what needs to be closed --
	if (pipex->cur_pipe[1] > 2)
		close(pipex->cur_pipe[1]);
	// --
}

void child_parse_and_exe(t_minishell minishell, t_tree_node *cmd_node, t_pipe_data *pipex, int idx)
{
	// cmd parse --
	if (cmd_node->right)
		pipex->cmd = matrix_add_front(cmd_node->cont.cmd, cmd_node->right->cont.args);
	else
		pipex->cmd = matrix_add_front(cmd_node->cont.cmd, NULL);
	if(!pipex->cmd)
		pipex_clean_up(); // fail fork abort
	
	// path parse --
	pipex->path = get_path(pipex->cmd[0], pipex->env);
	if (!pipex->path)
			pipex_clean_up(); // fail alloc abort
			
	// dupping --
	if (pipex->next_pipe[0] > 2)
		close(pipex->next_pipe[0]);
	if (pipex->cur_pipe[0] > 2)
		dup2(pipex->cur_pipe[0], STDIN_FILENO);
	// else no working infile??
	if (pipex->cur_pipe[1] > 2)
		dup2(pipex->cur_pipe[1], STDOUT_FILENO);
	master_close();
	
	// executing --
	if (execve(pipex->path, pipex->cmd, pipex->env) == -1)
		pipex_clean_up(); // fail fork abort
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

char	*get_path(char *cmds, char **env)
{
	char	**path;
	char	*joined;
	char	*bar;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (ft_strdup(cmds));
	i = -1;
	while (path[++i])
	{
		bar = ft_strjoin(path[i], "/");
		if (!bar)
			pipex_clean_up(); // fail alloc abort
		joined = ft_strjoin(bar, cmds);
		free(bar);
		if (!joined)
			pipex_clean_up(); // fail alloc abort
		if (access(joined, F_OK) == 0)
			return (free_split(path), joined);
		free(joined);
	}
	return (free_split(path), ft_strdup(cmds));
}

void assign_pipe_fds(t_minishell minishell, t_pipe_data *pipex, int *redir_fd, int idx)
{
	int new_pipe[2];
	
	if (pipex->cur_pipe[0] > 2)
		close (pipex->cur_pipe[0]);
	if (redir_fd[0] > 2) // in redir
	{
		pipex->cur_pipe[0] = redir_fd[0];
		if (pipex->next_pipe[0] > 2) // possible problem
			close(pipex->next_pipe[0]);
	}
	else // no redir in, input from pipe/stdin if prev cmd was redir out or cur is first
	{
		pipex->cur_pipe[0] = pipex->next_pipe[0];
		pipex->next_pipe[0] = 0;
	}
	if (redir_fd[1] > 2 || idx + 1 < pipex->cmd_n) // out redir or last cmd
		pipex->cur_pipe[1] = redir_fd[1];
	else // no redir, not last
	{
		if (pipe(new_pipe) == -1)
			pipex_clean_up(); // pipe didnt create abort
		pipex->cur_pipe[1] = new_pipe[1];
		pipex->next_pipe[0] = new_pipe[0];
	}
}

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
	if (*in == -1 || *out == -1) // NO MORE REDIRS ARE HANDLED and cmd doesnt execute?
		pipex_clean_up(); // write bash: cmd_node->left->cont.file: perror
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
			break; // CTRL D CASE
	}
	if (line)
		free(line);
	close(here_pipe[1]);
	return (here_pipe[0]);
}

void	multi_proc_wait(t_pipe_data *pipex, int *status)
{
	int	i;
	int	w_pid;
	int	exit_status;

	i = 0;
	*status = 0;
	w_pid = pipex->pid[0];
	while (i < pipex->cmd_n && w_pid != pipex->pid[pipex->cmd_n - 1])
	{
		w_pid = wait(&exit_status);
		i++;
	}
	while (i < pipex->cmd_n && w_pid == pipex->pid[pipex->cmd_n - 1])
	{
		wait(NULL);
		i++;
	}
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
}

void	pipex_clean_up(void)
{
	;
}
