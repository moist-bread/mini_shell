/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:04 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 13:30:33 by rduro-pe         ###   ########.fr       */
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
	minishell_struct_init(&ms, env);
	input = NULL;
	while (1)
	{
		input = fake_readinput(ms, input);
		tokens = create_tokens(input);
		if (!tokens)
			continue ;
		ms.tree_head = create_tree(&tokens, &ms);
		if (!ms.tree_head)
			return (syntax_clear(&tokens), minishell_clean(ms, 1), 1);
		fake_clear_token_lst(tokens);
		master_distributer(&ms, ms.tree_head);
		if (ms.tree_head)
			free_tree(&ms.tree_head);
	}
	return (minishell_clean(ms, ms.exit_status), 0);
}
