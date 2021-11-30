#include "../../../includes/minishell.h"

void	ft_unset(t_struct *s)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (s->bob->token[i] != NULL)
	{
		if (!ft_isalpha(s->bob->token[i][0]))
		{
			printf("export: \'%s\': not a valid identifier", s->bob->token[i]);
		}
		else
		{
			while (s->bob->token[i][j] != '=' && s->bob->token[i][j])
			{
				if (!ft_isalnum(s->bob->token[i][j]))
				{
					printf("export: \'%s\': not a valid identifier", s->bob->token[i]);
				}
				j++;
			}
			if (s->bob->token[i][j] == '=' || !s->bob->token[i][j])
			{
				while (s->env.next != NULL)
				{
					s->env = *s->env.next;
					if (ft_strncmp(s->env.content, s->bob->token[i], ft_strlen(s->bob->token[i])))
					{
						ft_lstdelone(&s->env, NULL);
						break ;
					}
				}
			}
		}
		i++;
	}
}
