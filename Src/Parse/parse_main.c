/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:09:32 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/11 12:52:02 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input = NULL;
	(void)ac;
	(void)av;
	(void)env;
	printf(YEL "Parse Main !\n" DEF);
	while(1)
	{
		input = readinput(input);
		create_tokens(input);
		free(input);
	}
	return (0);
}

// Split needs an upgrade. It needs to separate in spaces, pipes and redirections
// If is echo arguments appear with spaces even if i dindt have a space in the prompt
// Example:
// 			"echo ola>fd banana" - writes - "ola banana"
// Example:
// 			"''hola'''''''hola''''" - writes - 1:"hola"  2:"hola"