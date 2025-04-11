
#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Exec Main !\n" DEF);
	
	t_minishell minis;
	
	minis.env = env;
	minis.exit_status = 0;
	
	t_node_cont cont_1;
	t_pipe_data pipe_1;
	pipe_1.pid = ft_calloc(3, sizeof(int));
	pipe_1.env = minis.env;
	cont_1.pipe = pipe_1;
	minis.tree_head = newtreenode(cont_1);
	minis.tree_head->type = PIPE;

	t_node_cont cont_2;
	cont_2.cmd = NULL;
	minis.tree_head->right = newtreenode(cont_2);
	minis.tree_head->right->type = PIPE;



	return (0);
}
