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

void	ft_exit(t_struct *s)
{
	printf("exit\n");
	if (s->bob->token[1] == NULL)
	{
		g_errna = 0;
		exit(0);
	}
	else if (s->bob->token[1] && s->bob->token[2] != NULL)
		printf("too many arguments");
	else if (ft_checkdigit(s->bob->token[1]) == -1)
	{
		printf("numeric argument required\n");
		g_errna = 2;
		exit(2);
	}
	else
	{
		g_errna = atoi(s->bob->token[1]);
		exit(atoi(s->bob->token[1]));
	}
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
