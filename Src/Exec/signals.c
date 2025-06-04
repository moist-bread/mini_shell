
#include "../../Inc/minishell.h"

static void	parent_sig_handler(int signal);
static void	here_doc_sig_handler(int signal);

/// @brief Saves adress to MINISHELL in the global variable and
/// initialized the signals according to FLAG
/// @param minishell Overarching Minishell Structure
/// @param flag 'P': parent, 'H': here doc, 'I': ignore, 'D': default
void	init_sigact(t_minishell *minishell, int flag)
{
	struct sigaction	sa;

	mem_save(minishell);
	if (flag == 'D')
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	if (flag == 'P')
		sa.sa_handler = &parent_sig_handler;
	else if (flag == 'H')
		sa.sa_handler = &here_doc_sig_handler;
	sigaction(SIGINT, &sa, NULL);
}

t_minishell	*mem_save(t_minishell *minishell)
{
	static t_minishell	*ms_save;

	if (minishell)
	{
		ms_save = minishell;
		return (NULL);
	}
	else
		return (ms_save);
}

/// @brief Restarts readline in case of CTRL+C
static void	parent_sig_handler(int signal)
{
	t_minishell	*ms;

	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		ms = mem_save(NULL);
		ms->exit_status = 130;
	}
}

/// @brief Exits the Here Doc process in case of CTRL+C
static void	here_doc_sig_handler(int signal)
{
	if (signal == SIGINT)
		minishell_clean(*mem_save(NULL), 130);
}

/// @brief Basic error function
/// @param token Node of the token list
void	ft_error_check(t_token **token, int msg)
{
	t_minishell	*ms;

	ms = mem_save(NULL);
	ms->exit_status = 2;
	if (msg == 1)
		ft_printf_fd(2, "syntax error near unexpected token\n");
	if (msg == 2)
		ft_printf_fd(2, "Invalid Syntax\n");
	syntax_clear(token);
}
