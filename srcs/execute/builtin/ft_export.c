#include "../../../includes/minishell.h"

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	printf("%c\n", c);
	while ((ss1[i] != '\0' || ss2[i] != '\0') && (ss1[i] != c || ss2[i] != c))
	{
		if (ss1[i] - ss2[i] != 0)
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

void	ft_checkdup(t_struct *s, char *str)
{
	/*while (s->env->next != NULL)
	{
		s->env = *s->env->next;
		if (ft_strccmp(s->env->content, str, '=') == 0)
			ft_unset(s->env);
	}*/
}

void	ft_lstprint(t_list *lst)
{
	int		i;
	char	**mem;

	mem = NULL;
	i = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (ft_strchr(lst->content, '='))
		{
			mem = ft_split(lst->content, '=');
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
			printf("declare -x %s\n", lst->content);
	}
}

void	ft_lstcontent_swp(t_list *lst1, t_list *lst2)
{
	char	*str;

	str = lst2->content;
	lst2->content = lst1->content;
	lst1->content = str;
}

t_list	*ft_lstcopy(t_struct *s)
{
	t_list	*mem;

	mem = ft_lstnew(NULL);
	while (s->env->next != NULL)
	{
		ft_lstadd_back(&mem->next, ft_lstnew(s->env->content));
		s->env = s->env->next;
	}
	ft_lstadd_back(&mem->next, ft_lstnew(s->env->content));
	mem = mem->next;
	return (mem);
}

void	ft_lstc(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	current = current->next;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_lstsort_str(t_struct *s)
{
	t_list	*mem;
	t_list	*first;
	t_list	*sortlist;

	mem = ft_lstcopy(s);
	first = mem;
	sortlist = first;
	while (first->next != NULL)
	{
		first = first->next;
		mem = first;
		while (mem->next != NULL)
		{
			mem = mem->next;
			if (ft_strcmp(first->content, mem->content) > 0)
			{
				ft_lstcontent_swp(first, mem);
			}
		}
	}
	first = sortlist;
	ft_lstprint(first);
	ft_lstc(&sortlist);
}

void	ft_export(t_struct *s)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (s->bob->token[1] == NULL)
		ft_lstsort_str(s);
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
					ft_checkdup(s, s->bob->token[i]);
					ft_lstadd_back(&s->env->next, ft_lstnew(s->bob->token[i]));
				}
			}
			i++;
		}
	}
}
