
#include "../../Inc/minishell.h"

/*
int	main(int ac, char **av, char **env)
{
	t_minishell	minis;
	t_node_cont	cont_1;
	t_node_cont	cont_2;
	t_node_cont	cont_3;
	t_node_cont	cont_4;
	t_node_cont	cont_6;
	t_node_cont	cont_7;
	t_node_cont	cont_5;

	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Exec Main !" DEF "\n");
	minishell_struct_init(&minis, env);
	tree_cont_init(&cont_1);
	cont_1.pipe.cmd_n = 3;
	cont_1.pipe.pid = ft_calloc(3, sizeof(int));
	cont_1.pipe.env = minis.env;
	minis.tree_head = newtreenode(cont_1);
	minis.tree_head->type = PIPE;
	tree_cont_init(&cont_2);
	minis.tree_head->right = newtreenode(cont_2);
	minis.tree_head->right->type = PIPE;
	tree_cont_init(&cont_3);
	cont_3.cmd = ft_strdup("ls");
	minis.tree_head->left = newtreenode(cont_3);
	minis.tree_head->left->type = CMD;
	tree_cont_init(&cont_4);
	cont_4.cmd = ft_strdup("wc");
	minis.tree_head->right->left = newtreenode(cont_4);
	minis.tree_head->right->left->type = CMD;
	tree_cont_init(&cont_6);
	cont_6.file = ft_strdup("outfile");
	minis.tree_head->right->left->left = newtreenode(cont_6);
	minis.tree_head->right->left->left->type = REDIR_OUT_APPEND;
	tree_cont_init(&cont_7);
	cont_7.file = ft_strdup("gato");
	minis.tree_head->right->left->left->left = newtreenode(cont_7);
	minis.tree_head->right->left->left->left->type = REDIR_OUT_APPEND;
	tree_cont_init(&cont_5);
	cont_5.cmd = ft_strdup("banana");
	minis.tree_head->right->right = newtreenode(cont_5);
	minis.tree_head->right->right->type = CMD;
	pipex_process(&minis, minis.tree_head, &minis.tree_head->cont.pipe);
	printf("after pipex exit status: %d\n", minis.exit_status);
	pipex_clean_up(minis, minis.exit_status);
}*/
void	minishell_struct_init(t_minishell *minis, char **env)
{
	minis->tree_head = NULL;
	minis->env = matrix_dup_char(env);
	minis->exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minis;
	int			i;

	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "(new) Exec Main !" DEF "\n");
	minishell_struct_init(&minis, env);
	i = -1;
	while (++i < 3)
		printf("%s\n", minis.env[i]);
	minis.env = env_add_front("new sentence", minis.env);
	printf("\n");
	i = -1;
	while (++i < 4)
		printf("%s\n", minis.env[i]);
	pipex_clean_up(minis, minis.exit_status);
}
