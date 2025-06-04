/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:47:25 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 12:47:26 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static int	print_distribute_fd(const char *input, va_list args, int fd);

int	ft_printf_fd(int fd, const char *input, ...)
{
	va_list	args;
	int		cnt;

	va_start(args, input);
	cnt = 0;
	while (*input)
	{
		if (*input == '%')
			cnt += print_distribute_fd(++input, args, fd);
		else
		{
			write(fd, &*input, 1);
			cnt++;
		}
		input++;
	}
	va_end(args);
	return (cnt);
}

static int	print_distribute_fd(const char *input, va_list args, int fd)
{
	int	cnt;

	if (*input == 'c')
		cnt = ft_printchar_fd(va_arg(args, int), fd);
	if (*input == 's')
		cnt = ft_printstr_fd(va_arg(args, char *), fd);
	if (*input == 'p')
		cnt = ft_printptr_fd(va_arg(args, unsigned long), 1, fd);
	if (*input == 'd' || *input == 'i')
		cnt = ft_prtnb_base_fd(va_arg(args, int), "0123456789", 10, fd);
	if (*input == 'u')
		cnt = ft_prtnb_base_fd(va_arg(args, unsigned int), "0123456789", 10,
				fd);
	if (*input == 'x')
		cnt = ft_prtnb_base_fd(va_arg(args, unsigned int), "0123456789abcdef",
				16, fd);
	if (*input == 'X')
		cnt = ft_prtnb_base_fd(va_arg(args, unsigned int), "0123456789ABCDEF",
				16, fd);
	if (*input == '%')
		cnt = ft_printchar_fd('%', fd);
	return (cnt);
}
