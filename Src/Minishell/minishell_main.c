/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:09:32 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/05/16 18:50:32 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	ms;
	char		*input;
	t_token		*tokens;
	
	(void)ac;
	(void)av;
	(void)env;

	ft_printf_fd(1, YEL "TESTING MINISHELL MAIN" DEF "\n\n");
	minishell_struct_init(&ms, env);
	input = NULL;
	while(1)
	{
		// parsing
		input = fake_readinput(ms, input);
		tokens = create_tokens(input);
		ms.tree_head = create_tree(tokens, ms.env);
		fake_clear_token_lst(tokens);
		// execution
		master_distributer(&ms, ms.tree_head);
		if (ms.tree_head) // prep for next input
		{
			free_tree(ms.tree_head);
			ms.tree_head = NULL;
		}
	}
	minishell_clean(ms, ms.exit_status); // clean up
}