
#include "../../Inc/minishell.h"

t_minishell	*g_ms_struct;

static void	parent_sig_handler(int signal);
static void	here_doc_sig_handler(int signal);

/// @brief Saves adress to MINISHELL in the global variable and
/// initialized the signals according to FLAG
/// @param minishell Overarching Minishell Structure
/// @param flag 'P': parent, 'H': here doc, 'I': ignore, 'D': default
void	init_sigact(t_minishell *minishell, int flag)
{
	struct sigaction	sa;

	// save adress to minishell
	// if (minishell)
	g_ms_struct = minishell;
	// signal SIGQUIT
	if (flag == 'D')
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	// signal SIGINT
	if (flag == 'P')
		sa.sa_handler = &parent_sig_handler;
	else if (flag == 'H')
		sa.sa_handler = &here_doc_sig_handler;
	sigaction(SIGINT, &sa, NULL);
}

/// @brief Restarts readline in case of CTRL+C
static void	parent_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_ms_struct->exit_status = 130;
	}
}

/// @brief Exits the Here Doc process in case of CTRL+C
static void	here_doc_sig_handler(int signal)
{
	if (signal == SIGINT)
		minishell_clean(*g_ms_struct, 130);
}

/// @brief Basic error function
/// @param token Node of the token list
void	ft_error_check(t_token **token)
{
	printf("syntax error near unexpected token\n");
	g_ms_struct->exit_status = 2;
	syntax_clear(*token);
	*token = NULL;
}