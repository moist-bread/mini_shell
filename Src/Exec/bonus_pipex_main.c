/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:55:28 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/08 12:47:24 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	*pipex;
	int			status;
	int			i;

	if (argc < 5 || !*argv[2] || !*argv[3])
		pipex_free_exit(NULL, 1, 1);
	pipex_struct_init(&pipex, argc, argv, envp);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		here_doc_handler(pipex, argv[2]);
	i = -1;
	while (++i < pipex->count)
	{
		if (i + 1 != pipex->count)
			create_pipe(pipex, i);
		create_child_pro(pipex, i);
		if (i + 1 == pipex->count)
			close(pipex->fd[i][0]);
		else
			close(pipex->fd[i][1]);
	}
	multi_process_waiting(pipex, &status);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		unlink("here_doc");
	pipex_free_exit(pipex, 17, status);
}
