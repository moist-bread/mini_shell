
#include "../../Inc/minishell.h"

void	minishell_struct_init(t_minishell *minis, char **env)
{
	minis->tree_head = NULL;
	minis->env = matrix_dup_char(env); // needs proper env
	minis->env_start = 0;
	minis->exit_status = 0;
}
