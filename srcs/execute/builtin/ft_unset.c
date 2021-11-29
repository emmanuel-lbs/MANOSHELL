#include "../../minishell.h"

void	ft_unset(t_struct *s)
{
	char	**mem;
	int		i;

	i = 1;
	while (s->bob.content[i] != NULL)
	{
		if (!ft_isalpha(s->bob.content[i]))
		{
			erno = 1;
			printf("export: \'%s\': not a valid identifier", s->bob.content[i]);
		}
		else 
		{
			while (s->bob.content[i][j] != '=' && s->bob.content[i][j])
			{
				if (!ft_isalphanum(s->bob.content[i][j]))
				{
					erno = 1;
					printf("export: \'%s\': not a valid identifier", s->bob.content[i]);						
				}
				j++;
			}
			if (s->bob.content[i][j] == '=' || !s->bob.content[i][j])
			{
				while (s->env.next != NULL)
				{
					s->env = *s->env.next;
					if (ft_strncmp(s->env.content, s->bob.content[i], ft_strlen(s->bob.content[i])))
					{
						ft_lstdelone(s->env);
						break ;
					}
				}
			}
		}
		i++;
	}
}
