

#include "../../Inc/minishell.h"

/// @brief Length of new input
/// @param input 
/// @return length
int	space_length(char *input)
{
	int		i;
	int		spaces;

	i = -1;
	spaces = 0;
	while (input[++i])
	{
		if (input[i] == '\"')
		{
			while (ft_isprint(input[++i]) && input[i] != '\"')
				;
			i++;
		}
		else if (ft_strchr("|<>", input[i]))
		{
			if (input[i - 1] != ' ' && !ft_strchr("|<>", input[i - 1]))
				spaces++;
			if (input[i] == '|' || input[i] == input[i + 1])
				i++;
			if (input[i] != ' ')
				spaces++;
		}
	}
	return (spaces);
}

char	*space_put(char *input, int len)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = ft_calloc(len + ft_strlen(input) + 1, sizeof(char));
	while (input[i])
	{
		if (input[i] == '\"')
		{
			dest[j++] = input[i++];
			while (ft_isprint(input[i]) && input[i] != '\"')
				dest[j++] = input[i++];
			if (input[i] == '\"')
				dest[j++] = input[i++];
		}
		else if (ft_strchr("|<>", input[i]))
		{

			if (input[i - 1] != ' ' && !ft_strchr("|<>", input[i - 1]))
				dest[j++] = ' ';
			if (input[i] == '|' || input[i] == input[i + 1])
				dest[j++] = input[i++];
			dest[j++] = input[i];
			if (input[i] != ' ')
				dest[j] = ' ';



			// if (input[i - 1] != ' ' && !ft_strchr("|<>", input[i - 1]))
			// 	dest[j++] = ' ';
			// dest[j++] = input[i++];
			// if (input[i] != ' ' && input[i] != input[i + 1])
			// 	dest[j++] = ' ';
		}
		else
			dest[j] = input[i];
		printf("char i: %c, %d\n", input[i - 1], i - 1);
		printf("char j: %c, %d\n", dest[j - 1], j - 1);
		j++;
		i++;

	}
	dest[j] = '\0';
	printf("line: %s\n", dest);
	return (dest);
}

// char	*space_put(char *input, int len)
// {
//     int		i;
//     int		j;
//     char	*dest;

//     i = 0;
//     j = 0;
//     dest = ft_calloc(len + ft_strlen(input) + 1, sizeof(char)); // Allocate memory for the new string
//     if (!dest)
//         return (NULL);
//     while (input[i])
//     {
//         // Copy characters inside quotes as-is
//         if (input[i] == '\"')
//         {
//             dest[j++] = input[i++];
//             while (ft_isprint(input[i]) && input[i] != '\"')
//                 dest[j++] = input[i++];
//             if (input[i] == '\"')
//                 dest[j++] = input[i++];
//         }
//         // Handle special characters |, <, >
//         else if (ft_strchr("|<>", input[i]))
//         {
//             // Add a space before the special character if needed
//             if (i > 0 && input[i - 1] != ' ' && !ft_strchr("|<>", input[i - 1]))
//                 dest[j++] = ' ';
//             dest[j++] = input[i++]; // Copy the special character
//             // Add a space after the special character if needed
//             if (input[i] && input[i] != ' ' && !ft_strchr("|<>", input[i]))
//                 dest[j++] = ' ';
//         }
//         // Copy regular characters
//         else
//         {
//             dest[j++] = input[i++];
//         }
//     }
//     dest[j] = '\0'; // Null-terminate the string
//     printf("line: %s\n", dest);
//     return (dest);
// }
