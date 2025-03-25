/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andcarva <andcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:52:57 by andcarva          #+#    #+#             */
/*   Updated: 2025/02/17 16:53:08 by andcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*line;
	int				len;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (*buffer || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_line(line, buffer);
		if (!line)
			return (free(line), NULL);
		ft_buff_move(buffer);
		len = ft_linelen(line);
		if (line[len - 1] == '\n')
			return (line);
	}
	return (line);
}

// int main(void)
// {
//     int fd = open("text.txt", O_RDONLY);
//     char *line;
// 	int		i = 0;
	
//     if (fd == -1)
//     {
//         printf("Error opening file");
//         return 1;
// 	}
//     while (i < 5)
//     {
// 		line = get_next_line(fd);
// 		if (line != NULL)
// 		{
//     	    printf("line: %s", line);
//     		free(line);
// 		}
// 		i++;
//     }
//     close(fd);
//     return 0;
// }