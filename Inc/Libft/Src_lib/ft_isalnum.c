/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:45:33 by andre             #+#    #+#             */
/*   Updated: 2025/04/03 15:09:19 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/* int main() {
    char c = '?';

    if (isalnum(c)) {
        printf("System: %c is alphanumeric.\n", c);
    } else {
        printf("System: %c is not alphanumeric.\n", c);
    }

	 if (ft_isalnum(c)) {
        printf("mine: %c is alphanumeric.\n", c);
    } else {
        printf("mine: %c is not alphanumeric.\n", c);
    }

    return 0;
} */