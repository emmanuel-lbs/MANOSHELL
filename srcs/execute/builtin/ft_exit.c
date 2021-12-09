#include "../../../includes/minishell.h"

static int	ft_checkdigit(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			return (-1);
		i++;
	}
	return (1);
}

void	ft_exit(t_struct *s)
{
	printf("exit\n");
	if (s->bob->token[1] == NULL)
		exit(sim);
	else if (s->bob->token[1] && s->bob->token[2] != NULL)
		printf("too many arguments");
	else if (ft_checkdigit(s) == -1)
	{
		printf("numeric argument required\n");
		exit(2);
	}
	else
		exit(atoi(s->bob->token[1]));
}

void	ft_pipexit(t_struct *s)
{
	if (s->bob->token[1] && s->bob->token[2] != NULL)
		sim = 1;
	else if (ft_checkdigit(s) == -1)
		sim = 2;
	else
		sim = atoi(s->bob->token[1]);
}
