#include "../../../includes/minishell.h"

static int	ft_checkdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

static void ft_print_exit(t_struct *s, char *str, int error)
{
	tcsetattr(0, TCSANOW, &s->old_termios);
	printf("%s\n", str)
	g_errna = error;
	exit(error);
}

void	ft_exit(t_struct *s)
{
	if (s->bob->token[1] == NULL)
		ft_print_exit("exit \n", 0);
	else if (s->bob->token[1] && s->bob->token[2] != NULL)
		ft_print_exit("exit: too many arguments\n", 1);
	else if (ft_checkdigit(s->bob->token[1]) == -1)
		ft_print_exit("exit: numeric argument required\n", 2);
	else
		ft_print_exit("exit \n", atoi(s->bob->token[1]));		
}

void	ft_pipexit(t_struct *s)
{
	if (s->bob->token[1] && s->bob->token[2] != NULL)
		g_errna = 1;
	else if (ft_checkdigit(s->bob->token[1]) == -1)
		g_errna = 2;
	else
		g_errna = atoi(s->bob->token[1]);
}
