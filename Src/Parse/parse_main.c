/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:09:32 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/08 12:57:17 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Parse Main !\n" DEF);
	while(1)
	{
		input = readline("minishell > ");
		if (!input)
		{
			free(input);
			exit(0);
		}
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
			exit (0);
		free(input);
	}
	return (0);
}