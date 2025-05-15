
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