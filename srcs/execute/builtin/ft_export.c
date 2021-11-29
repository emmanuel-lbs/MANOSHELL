#include "../../minishell.h"

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
//	if (s->bob.content[1] == NULL)
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
//		while (s->bob.content[i])
//		{
//			ft_lstadd_front(&s->env.next, ft_lstnew(envp[i]));
//			i++;
//		}
//		
//	}
//}

//AVEC UN SPLIT
void	ft_export(t_struct *s)
{
	char	**mem;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (s->bob.content[1] == NULL)
	{
		ft_lst_sort_str(s->env);
		while (s->env.next != NULL)
		{
			s->env = *s->env.next;
			if (ft_strchr(s->env.content, '='))
			{
				mem = ft_split(s->env.content, '=');
				printf("declare -x %s\"", mem[0]);
				while (mem && mem[i])
				{
					printf("%s", mem[i]);
					i++;
				}
				i = 1;
				printf("\"\n");
			}
			else
				printf("declare -x %s",s->env.content);
		}
	}
	else
	{
		while (s->bob.content[i])
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
					ft_lstadd_front(&s->env.next, ft_lstnew(envp[i]));
			}
			i++;
		}
		
	}
}
