/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:10:31 by andcarva          #+#    #+#             */
/*   Updated: 2025/04/02 17:08:17 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchartf(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstrtf(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

static int	ft_percentage(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		arg;
	int			print;

	va_start(arg, str);
	i = 0;
	print = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			print += ft_printf_rules(str[i + 1], arg);
			i++;
		}
		else
			print += ft_putchartf(str[i]);
		i++;
	}
	va_end(arg);
	return (print);
}

int	ft_printf_rules(const char spec, va_list list)
{
	int	print;

	print = 0;
	if (spec == 'c')
		print += ft_putchartf(va_arg(list, int));
	else if (spec == 's')
		print += ft_putstrtf(va_arg(list, char *));
	else if (spec == 'p')
		print += ft_put_ptr(va_arg(list, uintptr_t));
	else if (spec == 'd' || spec == 'i')
		print += ft_put_nbr_tf(va_arg(list, int));
	else if (spec == 'u')
		print += ft_put_un_nbr(va_arg(list, unsigned int));
	else if (spec == 'x')
		print += ft_put_nbr_base(va_arg(list, unsigned int), HEX_LB);
	else if (spec == 'X')
		print += ft_put_nbr_base(va_arg(list, unsigned int), HEX_UPB);
	else if (spec == '%')
		print += ft_percentage();
	return (print);
}
