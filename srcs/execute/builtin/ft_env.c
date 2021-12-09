#include "../../../includes/minishell.h"

void ft_env(t_struct *s)
{
	if (s->bob->token[1] != NULL)
	{
		printf("env: Invalid number of arguments\n");
		exit(1);
	}
	while (s->env.next != NULL)
	{
		if (ft_strchr(s->env.content, '=') != NULL)
			printf("%s\n", s->env.content);
		s->env = *s->env.next;
	}
}
