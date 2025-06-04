/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:47:28 by rduro-pe          #+#    #+#             */
/*   Updated: 2025/06/04 12:47:29 by rduro-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf_fd(int fd, const char *input, ...);
int	ft_printchar_fd(int c, int fd);
int	ft_printstr_fd(char *str, int fd);
int	ft_prtnb_base_fd(long nbr, char *base, int len, int fd);
int	ft_printptr_fd(unsigned long p, int flag, int fd);

#endif