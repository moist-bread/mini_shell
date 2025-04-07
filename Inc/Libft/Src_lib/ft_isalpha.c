/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:29:58 by andre             #+#    #+#             */
/*   Updated: 2025/04/03 15:09:19 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/* int main() {
    char c = '0';

    if (isalpha(c)) {
        printf("System: %c is an alphabetic letter.\n", c);
    } else {
        printf("System: %c is not an alphabetic letter.\n", c);
    }

	if (ft_isalpha(c)) {
        printf("mine: %c is an alphabetic letter.\n", c);
    } else {
        printf("mine: %c is not an alphabetic letter.\n", c);
    }

    return 0;
} */