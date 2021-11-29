#include "../../minishell.h"

void ft_env(t_struct *s)
{
	if (s->bob.content[1] = NULL)
	{
		erno = 1;
		printf("env: Invalid number of arguments\n");
		exit(1);
	}
	while (s->env.next != NULL)
	{
	  s->env = *s->env.next;
	}
}
