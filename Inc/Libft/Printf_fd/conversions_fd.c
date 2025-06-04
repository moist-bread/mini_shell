/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:47:19 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 12:47:20 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_printchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printstr_fd(char *str, int fd)
{
	int	cnt;

	if (!str)
		str = "(null)";
	cnt = 0;
	while (*str)
	{
		write(fd, &*str++, 1);
		cnt++;
	}
	return (cnt);
}

int	ft_prtnb_base_fd(long nbr, char *base, int len, int fd)
{
	int	cnt;
	int	mod;

	cnt = 0;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
		cnt++;
	}
	if (nbr >= len)
		cnt += ft_prtnb_base_fd(nbr / len, base, len, fd);
	mod = nbr % len;
	write(fd, &base[mod], 1);
	cnt++;
	return (cnt);
}

int	ft_printptr_fd(unsigned long p, int flag, int fd)
{
	int	cnt;
	int	mod;

	cnt = 0;
	if (!p)
		return (ft_printstr_fd("(nil)", fd));
	if (flag)
		cnt += write(fd, "0x", 2);
	if (p >= 16)
		cnt += ft_printptr_fd(p / 16, 0, fd);
	mod = p % 16;
	cnt += write(fd, &"0123456789abcdef"[mod], 1);
	return (cnt);
}
