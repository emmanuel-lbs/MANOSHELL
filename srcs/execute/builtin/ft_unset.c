#include "../../../includes/minishell.h"

void	ft_delone(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp->next;
	tmp->next = tmp->next->next;
	free(mem);
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
			printf("export: \'%s\': not a valid identifier\n", s->bob->token[i]);
		}
		else
		{
			while (s->bob->token[i][j] != '=' && s->bob->token[i][j])
			{
				if (!ft_isalnum(s->bob->token[i][j]))
				{
					printf("export: \'%s\': not a valid identifier\n", s->bob->token[i]);
				}
				j++;
			}
			if (s->bob->token[i][j] == '=' || !s->bob->token[i][j])
			{
				while (s->env->next != NULL)
				{
					if (ft_strchr(s->bob->token[i], '=') != 0)
					{
						if (ft_strccmp(s->env->next->content, s->bob->token[i], '=') == 0)
						{
							printf("next = %s\n", s->env->next->content);
							ft_delone(&s->env);
							break ;
						}
					}
					else
					{
						if (ft_strcmp(s->env->next->content, s->bob->token[i]) == 0)
						{
							printf("next = %s\n", s->env->next->content);
							ft_delone(&s->env);
							break ;
						}
					}
					s->env = s->env->next;
				}
			}
		}
		i++;
	}
}
