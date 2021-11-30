#include "../../../includes/minishell.h"

// A TESTER !!!
// A TESTER !!!
// A TESTER !!!
// A TESTER !!!
// A TESTER !!!
//void	ft_export(t_struct *s)
//{
//	char	*mem;
//	char	*arg;
//	int		i;
//	int		j;
//
//	i = 1;
//	j = 0;
//	if (s->bob->token[1] == NULL)
//	{
//		ft_lst_sort_str(s->env);
//		while (s->env.next != NULL)
//		{
//			s->env = *s->env.next;
//			mem = ft_strchr(s->env.content, '=');
//			if (mem)
//			{
//				arg = malloc(sizeof(char *) * ft_strlen(mem) + 1);
//				while(mem && mem[i])
//				{
//					arg[j] = mem[i]
//					i++;
//					j++;
//				}
//				arg[j] = '\0';
//				i = 1;
//				j = 0;
//				printf("declare -x %s\"%s\"",s->env.content - ft_strlen(mem - 1), arg);
//			}
//			else
//				printf("declare -x %s",s->env.content);
//		}
//	}
//	else
//	{
//		while (s->bob->token[i])
//		{
//			ft_lstadd_front(&s->env.next, ft_lstnew(envp[i]));
//			i++;
//		}
//		
//	}
//}

//AVEC UN SPLIT
t_list	*ft_searchdup(t_struct *s, char *str)
{
	while (s->env.next != NULL)
	{
		s->env = *s->env.next;
		if (s->env.content == 
	}
}

void	ft_export(t_struct *s)
{
	char	**mem;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (s->bob->token[1] == NULL)
	{
		//ft_lstsort_str(s->env);
		while (s->env.next != NULL)
		{
			s->env = *s->env.next;
			if (ft_strchr(s->env.content, '='))
			{
				mem = ft_split(s->env.content, '=');
				printf("declare -x %s=\"", mem[0]);
				while (mem && mem[i])
				{
					printf("%s", mem[i]);
					i++;
				}
				i = 1;
				printf("\"\n");
			}
			else
				printf("declare -x %s\n",s->env.content);
		}
		s->env = *s->first;
	}
	else
	{
		while (s->bob->token[i])
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
					ft_lstadd_back(&s->env.next, ft_lstnew(s->bob->token[i]));
				}
			}
			i++;
		}
	}
}
