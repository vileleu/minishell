#include "minishell.h"

int		loop(char *s)
{
	char	**cmd;
	char	*line;
	int		i;

	while (1)
	{
		ft_putstr(s + 2);
		ft_putstr(": ");
		if ((get_next_line(0, &line)) <= 0)
			return(ft_error("can't read on strdout"));
		ft_putstr(line);
		ft_putstr("\n");
		cmd = ft_split(line, ' ');
		i = 0;
		while (cmd[i])
		{
			ft_putstr(cmd[i++]);
			ft_putchar_fd('\n', 1);
		}
	}
}

int		main(int ac, char **av)
{
	if (ac != 1)
		return (ft_error("too many arguments"));
	loop(av[0]);
	return (0);
}