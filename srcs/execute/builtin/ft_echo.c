#include "../../../includes/minishell.h"

static int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (!str[i] || !(str[0] == '-'))
		return (-1);
	i = 1;
	while (str[i])
	{	
		if (str[i] == 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_write_echo(t_struct *s)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (echo_flag(s->bob->token[++i]) == 1)
		flag = 1;
	while (s->bob->token[i])
	{
		while (s->bob->token[i][j])
		{
			write(1, &s->bob->token[i][j], 1);
			j++;
		}
		j = 0;
		if (s->bob->token[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	ft_echo(t_struct *s)
{
	if (!s->bob->token[1])
		printf("\n");
	else
		ft_write_echo(s);
}