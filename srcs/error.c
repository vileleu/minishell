#include "minishell.h"

int		ft_error(char *s)
{
	ft_putstr("Error: ");
	ft_putstr(s);
	ft_putstr("\n");
	return (0);
}