
#include "../../Inc/minishell.h"

t_minishell				*g_ms_struct;

void	parent_sig_handler(int signal)
{
	// only act for sigint
	// do a new readline line
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	child_sig_handler(int signal)
{
	// only act for sigint
	// exit and clean everything
	if (signal == SIGINT)
	{
		printf("CLEAN DIA WTHHH\n");
		//minishell_clean(*g_ms_struct, g_ms_struct->exit_status);
	}
	if (signal == SIGQUIT)
	{
		printf("funcionas ou não bro??\n");
		//minishell_clean(*g_ms_struct, g_ms_struct->exit_status);
	}
}

void	here_doc_sig_handler(int signal)
{
	// only act for sigint
	// exit and clean everything
	if (signal == SIGINT)
	{
		//printf("HER WE CLEAN\n");
		minishell_clean(*g_ms_struct, g_ms_struct->exit_status);
	}
}

void	ign_sig_handler(int signal)
{
	// settings that ignore stuff
	// or do it the default way??
	// use the ignore for when child pros are iniciated
	if (signal == SIGINT)
	{
		printf("HER WE CLEAN\n");
	}
}
// 4 handlers
// parent_handler
// child_handler
// here_doc_handler
// ignore_handler (parent while child)

void	init_sigact(t_minishell *minishell, int flag)
{
	struct sigaction	sa;

	if (minishell)
		g_ms_struct = minishell;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	if (flag == 'P')
		sa.sa_handler = &parent_sig_handler;
	else if (flag == 'C')
	{
		sa.sa_handler = &child_sig_handler;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (flag == 'H')
		sa.sa_handler = &here_doc_sig_handler;
	else if (flag == 'I')
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}
