/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_hexfunc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:55:45 by andcarva          #+#    #+#             */
/*   Updated: 2024/12/09 15:18:32 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_nbr_base(unsigned int nbr, char *base)
{
	unsigned int	result;
	size_t			len;
	char			c;

	result = 0;
	len = ft_strlen(base);
	if (nbr >= len)
	{
		result += ft_put_nbr_base(nbr / len, base);
		result += ft_put_nbr_base(nbr % len, base);
	}
	else
	{
		c = base[nbr];
		result += write(1, &c, 1);
	}
	return (result);
}

static int	ft_put_nbr_ptr(uintptr_t nbr, char *base)
{
	unsigned int		result;
	size_t				len;
	char				c;

	result = 0;
	len = ft_strlen(base);
	if (nbr >= len)
	{
		result += ft_put_nbr_ptr(nbr / len, base);
		result += ft_put_nbr_ptr(nbr % len, base);
	}
	else
	{
		c = base[nbr];
		result += write(1, &c, 1);
	}
	return (result);
}

int	ft_put_ptr(uintptr_t ptr)
{
	int	print;

	print = 0;
	if (!ptr)
		print += write(1, "(nil)", 5);
	else
	{
		print += write(1, "0x", 2);
		print += ft_put_nbr_ptr(ptr, HEX_LB);
	}
	return (print);
}
