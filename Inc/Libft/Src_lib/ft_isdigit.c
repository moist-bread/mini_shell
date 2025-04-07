/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:37:06 by andre             #+#    #+#             */
/*   Updated: 2025/04/03 15:09:19 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* int main() {
    char c = 'a';

    if (isdigit(c)) {
        printf("System: %c is a digit.\n", c);
    } else {
        printf("System: %c is not a digit.\n", c);
    }

	 if (ft_isdigit(c)) {
        printf("mine: %c is a digit.\n", c);
    } else {
        printf("mine: %c is not a digit.\n", c);
    }

    return 0;
} */