
#include "../../Inc/minishell.h"

int	ft_iswhitespace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
