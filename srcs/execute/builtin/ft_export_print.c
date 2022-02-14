#include "../../../includes/minishell.h"

static void	ft_checkequal(t_list *lst, int i, char **mem)
{
	if (ft_strchr(lst->content, '='))
	{
		mem = ft_splitone(lst->content, '=', 0);
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

void	ft_lstprint(t_list *lst)
{
	int		i;
	char	**mem;

	mem = NULL;
	i = 1;
	while (lst->next != NULL)
	{
		ft_checkequal(lst, i, mem);
		lst = lst->next;
	}
	ft_checkequal(lst, i, mem);
}