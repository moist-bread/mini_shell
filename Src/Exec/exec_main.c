
#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Exec Main !" DEF "\n");
	
	t_minishell minis;
	
	minis.env = env;
	minis.exit_status = 0;
	
	t_node_cont cont_1;
	tree_cont_init(&cont_1);
	cont_1.pipe.cmd_n = 3;
	cont_1.pipe.pid = ft_calloc(3, sizeof(int));
	cont_1.pipe.env = minis.env;
	minis.tree_head = newtreenode(cont_1);
	minis.tree_head->type = PIPE;

	t_node_cont cont_2;
	tree_cont_init(&cont_2);
	minis.tree_head->right = newtreenode(cont_2);
	minis.tree_head->right->type = PIPE;

	t_node_cont cont_3;
	tree_cont_init(&cont_3);
	cont_3.cmd = ft_strdup("ls");
	minis.tree_head->left = newtreenode(cont_3);
	minis.tree_head->left->type = CMD;

	t_node_cont cont_4;
	tree_cont_init(&cont_4);
	cont_4.cmd = ft_strdup("wc");
	minis.tree_head->right->left = newtreenode(cont_4);
	minis.tree_head->right->left->type = CMD;

	t_node_cont cont_6;
	tree_cont_init(&cont_6);
	cont_6.file = ft_strdup("outfile");
	minis.tree_head->right->left->left = newtreenode(cont_6);
	minis.tree_head->right->left->left->type = REDIR_OUT_APPEND;

	t_node_cont cont_7;
	tree_cont_init(&cont_7);
	cont_7.file = ft_strdup("gato");
	minis.tree_head->right->left->left->left = newtreenode(cont_7);
	minis.tree_head->right->left->left->left->type = REDIR_OUT_APPEND;

	t_node_cont cont_5;
	tree_cont_init(&cont_5);
	cont_5.cmd = ft_strdup("banana");
	minis.tree_head->right->right = newtreenode(cont_5);
	minis.tree_head->right->right->type = CMD;

	pipex_process(&minis, minis.tree_head, &minis.tree_head->cont.pipe);
	
	printf("after pipex exit status: %d\n", minis.exit_status);
	free_tree(minis.tree_head);
	return (0);
}
