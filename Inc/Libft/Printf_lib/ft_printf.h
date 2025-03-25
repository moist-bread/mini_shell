/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:48:56 by andcarva          #+#    #+#             */
/*   Updated: 2024/12/09 16:07:20 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>

# define HEX_LB "0123456789abcdef"
# define HEX_UPB "0123456789ABCDEF"

int		ft_printf(const char *str, ...);
int		ft_printf_rules(const char spec, va_list list);
int		ft_putchartf(int c);
int		ft_putstrtf(char *str);
int		ft_put_nbr_tf(int nbr);
// int		ft_ulength(unsigned int n);
// char	*ft_unitoa(unsigned int n);
int		ft_put_un_nbr(unsigned int n);
// int		ft_percentage(void);
int		ft_put_nbr_base(unsigned int nbr, char *base);
// int		ft_put_nbr_ptr(uintptr_t nbr, char *base);
int		ft_put_ptr(uintptr_t ptr);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);

#endif // FT_PRINTF_H