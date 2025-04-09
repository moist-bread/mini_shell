/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:09:32 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/04/09 17:04:39 by andcarva         ###   ########.fr       */
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
		readinput(input);
		free(input);
	}
	return (0);
}