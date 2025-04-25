
#include "../../Inc/minishell.h"

/* int	main(int ac, char **av, char **env)
{
	t_minishell	minis;
	t_node_cont	cont_1;
	t_node_cont	cont_2;
	t_node_cont	cont_3;
	t_node_cont	cont_4;
	t_node_cont	cont_6;

	// main for pipex testing
	printf(YEL "Exec Main !" DEF "\n");
	(void)ac;
	(void)av;
	// handmade tree pls dont judge
	//t_node_cont	cont_7;
	//t_node_cont	cont_5;
	minishell_struct_init(&minis, env);
	tree_cont_init(&cont_1);
	cont_1.pipe.cmd_n = 2;
	cont_1.pipe.pid = ft_calloc(2, sizeof(int));
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
	cont_4.cmd = ft_strdup("cat");
	minis.tree_head->right->left = newtreenode(cont_4);
	minis.tree_head->right->left->type = CMD;
	tree_cont_init(&cont_6);
	cont_6.file = ft_strdup("LIM");
	minis.tree_head->right->left->left = newtreenode(cont_6);
	minis.tree_head->right->left->left->type = REDIR_HERE_DOC;
	// tree_cont_init(&cont_7);
	// cont_7.file = ft_strdup("gato");
	// minis.tree_head->right->left->left->left = newtreenode(cont_7);
	// minis.tree_head->right->left->left->left->type = REDIR_OUT;
	// tree_cont_init(&cont_5);
	// cont_5.cmd = ft_strdup("ls");
	// minis.tree_head->right->right = newtreenode(cont_5);
	// minis.tree_head->right->right->type = CMD;
	pipe_process(&minis, &minis.tree_head->cont.pipe);
	printf("after pipex exit status: %d\n", minis.exit_status);
	minishell_clean(minis, minis.exit_status);
} */
void	minishell_struct_init(t_minishell *minis, char **env)
{
	minis->tree_head = NULL;
	minis->env = matrix_dup_char(env); // make it cooler
	minis->env_lim = ft_matrixlen(minis->env) - 1;
	minis->exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	ms;
	t_node_cont	cont_1;
	t_node_cont	cont_2;

	// main for env testing
	(void)ac;
	(void)av;
	printf(YEL "(new) Exec Main !" DEF "\n");
	minishell_struct_init(&ms, env);
	tree_cont_init(&cont_1);
	ms.tree_head = newtreenode(cont_1);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("export");
	tree_cont_init(&cont_2);
	ms.tree_head->right = newtreenode(cont_2);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("BANANA+=novacena", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("ARGUMENTO+=isto", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("OUTRACOISA=velhacena", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("ARGUMENT", ms.tree_head->right->cont.args);
	print_env(ms, 1);
	printf("\n");
	export_built_in(&ms, ms.tree_head);
	print_env(ms, 1);
	printf("\n");
	print_env(ms, 0);
	minishell_clean(ms, ms.exit_status);
}
