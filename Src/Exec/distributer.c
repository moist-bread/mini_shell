
#include "../../Inc/minishell.h"

void	master_distributer(t_minishell *ms)
{
	if (!ms->tree_head)
		return ;
	if (ms->tree_head->type == CMD)
		; // coming soon
	else if (ms->tree_head->type == PIPE)
		pipe_process(ms, &ms->tree_head->cont.pipe);
	else if (ms->tree_head->type == BUILT_IN)
	{
		if (!ft_strcmp("echo", ms->tree_head->cont.cmd))
			echo_built_in(ms, ms->tree_head);
		else if (!ft_strcmp("cd", ms->tree_head->cont.cmd))
			; // coming soon
		else if (!ft_strcmp("pwd", ms->tree_head->cont.cmd))
			; // coming soon
		else if (!ft_strcmp("export", ms->tree_head->cont.cmd))
			export_built_in(ms, ms->tree_head);
		else if (!ft_strcmp("unset", ms->tree_head->cont.cmd))
			unset_built_in(ms, ms->tree_head);
		else if (!ft_strcmp("env", ms->tree_head->cont.cmd))
			env_built_in(ms, ms->tree_head);
		else if (!ft_strcmp("exit", ms->tree_head->cont.cmd))
			exit_built_in(ms, ms->tree_head);
	}
	if (ms->tree_head)
		free_tree(ms->tree_head);
}
