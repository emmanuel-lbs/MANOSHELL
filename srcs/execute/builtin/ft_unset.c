#include "../../../includes/minishell.h"

void	ft_delone(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp->next;
	tmp->next = tmp->next->next;
	while (tmp->next)
	{
		printf(" %s\n", tmp->content);
		tmp = tmp->next;
	}
	printf(" %s\n", tmp->content);
}

void	ft_unset(t_struct *s)
{
	int		i;
	int		j;
	t_list	*mem;
	t_list	*tmp;

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
					if (ft_strncmp(s->env.next->content, s->bob->token[i], ft_strlen(s->bob->token[i])) == 0)
					{
						printf("next = %s\n", s->env.next->content);
						tmp = &s->env;
						ft_delone(&tmp);
						break ;
					}
					s->env = *s->env.next;
				}
			}
		}
		i++;
	}
}
