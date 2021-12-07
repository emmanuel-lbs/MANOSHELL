#include "../../../includes/minishell.h"

void	ft_lstprint(t_list lst)
{
	while (lst.next != NULL)
	{
		lst = lst.next;
		if (ft_strchr(lst.content, '='))
		{
			mem = ft_split(lst.content, '=');
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
			printf("declare -x %s\n",lst.content);
	}
}

void	ft_lstsort_str(t_struct *s)
{
	t_list	mem;
	t_list	first;
	t_list	sortlist;
	char	*str;
	
	first = mem;
	sortlist = mem;
	while (s->env.next != NULL)
	{
		s->env = *s->env.next;
		ft_lstadd_back(&mem.next, s->env.content);
	}
	mem = first;
	while (first.next != NULL)
	{
		first = first.next;
		while (mem.next != NULL)
		{
			mem = mem.next
			if (ft_strcmp(first.content, mem.content) > 0)
			{
				str = first.content;
				first.content = mem.content;
				mem.content = str;
			}
		}
		mem = first;
	}
	ft_lstprint(sortlist);
	//ft_lstclear(sortlist);
}

void	ft_export(t_struct *s)
{
	char	**mem;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (s->bob->token[1] == NULL)
		ft_lstsort_str(s->env);
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
