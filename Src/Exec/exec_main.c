
#include "../../Inc/minishell.h"

/* int	main(int ac, char **av, char **env)
{
	t_minishell	minis;
	t_node_cont	cont_1;
	t_node_cont	cont_2;
	t_node_cont	cont_3;
	t_node_cont	cont_4;
	t_node_cont	cont_6;

	// main for pipe testing
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
	cont_1.pipe.env = minis.env[minis.env_start];
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
	printf("after pipe exit status: %d\n", minis.exit_status);
	minishell_clean(minis, minis.exit_status);
} */

void	minishell_struct_init(t_minishell *minis, char **env)
{
	minis->tree_head = NULL;
	minis->env = matrix_dup_char(env); // make it cooler
	minis->env_start = 0;
	minis->exit_status = 0;
}
/* int	main(int ac, char **av, char **env)
{
	t_minishell	ms;
	t_node_cont	cont_1;
	t_node_cont	cont_2;

	// main for export and unset testing
	(void)ac;
	(void)av;
	printf(YEL "(new) Exec Main !" DEF "\n\n");
	minishell_struct_init(&ms, env);
	tree_cont_init(&cont_1);
	ms.tree_head = newtreenode(cont_1);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("export");
	tree_cont_init(&cont_2);
	ms.tree_head->right = newtreenode(cont_2);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("COISA=COISA", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("BANANO=muita", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("BANANA", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("ARG=umento", ms.tree_head->right->cont.args);
	print_env(ms, 1);
	printf("\n");
	print_env(ms, 0);
	printf("\n");
	export_built_in(&ms, ms.tree_head);
	printf("\n");
	print_env(ms, 1);
	printf("\n");
	print_env(ms, 0);

	t_node_cont	cont_3;
	t_node_cont	cont_4;

	if (ms.tree_head)
		free_tree(ms.tree_head);
	tree_cont_init(&cont_3);
	ms.tree_head = newtreenode(cont_3);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("unset");
	tree_cont_init(&cont_4);
	ms.tree_head->right = newtreenode(cont_4);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("ARG", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("OUTRO", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("BANANA", ms.tree_head->right->cont.args);
	
	unset_built_in(&ms, ms.tree_head);

	printf("\n");
	print_env(ms, 1);
	printf("\n");
	print_env(ms, 0);

	minishell_clean(ms, ms.exit_status);
} */

/* 
int	main(int ac, char **av, char **env)
{
	t_minishell	ms;
	t_node_cont	cont_1;
	t_node_cont	cont_2;

	// main for echo and env testing
	(void)ac;
	(void)av;
	printf(YEL "(new) Exec Main !" DEF "\n\n");
	minishell_struct_init(&ms, env);
	tree_cont_init(&cont_1);
	ms.tree_head = newtreenode(cont_1);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("echo");
	tree_cont_init(&cont_2);
	ms.tree_head->right = newtreenode(cont_2);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("ARG=umento", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("BANANO=muita", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("BANANA", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("-nnnnnannnn", ms.tree_head->right->cont.args);
	
	echo_built_in(&ms, ms.tree_head);

	
	t_node_cont	cont_3;
	t_node_cont	cont_4;

	if (ms.tree_head)
		free_tree(ms.tree_head);
	tree_cont_init(&cont_3);
	ms.tree_head = newtreenode(cont_3);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("env");

	env_built_in(&ms, ms.tree_head);

	tree_cont_init(&cont_4);
	ms.tree_head->right = newtreenode(cont_4);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("ARG", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("OUTRO", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("-BANANA", ms.tree_head->right->cont.args);
	
	env_built_in(&ms, ms.tree_head);

	minishell_clean(ms, ms.exit_status);
} */


int	main(int ac, char **av, char **env)
{
	(void)env;
	(void)ac;
	(void)av;
	
	printf(YEL "(new) Testing exit built in main !" DEF "\n\n");

	/* if (!av[1])
		return (printf("whomp whomp\n"));
	printf("number: %s\n", av[1]); */
	
	t_minishell	ms;
	t_node_cont	cont_1;
	t_node_cont	cont_2;
	
	minishell_struct_init(&ms, env);
	tree_cont_init(&cont_1);
	ms.tree_head = newtreenode(cont_1);
	ms.tree_head->type = BUILT_IN;
	ms.tree_head->cont.cmd = ft_strdup("exit");
	tree_cont_init(&cont_2);
	ms.tree_head->right = newtreenode(cont_2);
	ms.tree_head->right->type = ARG;
	ms.tree_head->right->cont.args = matrix_add_front("ARG=umento", NULL);
	ms.tree_head->right->cont.args = matrix_add_front("BANANO=muita", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("BANANA", ms.tree_head->right->cont.args);
	ms.tree_head->right->cont.args = matrix_add_front("10", ms.tree_head->right->cont.args);
	
	master_distributer(&ms);
	free_split(ms.env);
	/* long n;
	if (long_check(av[1], &n) )
		printf("%ld IS WITHIN LONG!\n", n);
	else
		printf("overflowing . . .\n"); */
}
