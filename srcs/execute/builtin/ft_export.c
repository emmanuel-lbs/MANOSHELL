#include "../../../includes/minishell.h"

static void	ft_exportall(t_struct *s, int i, int j)
{
	if (!ft_isalpha_(s->bob->token[i][0]))
	{
		g_errna = 1;
		printf("export: \'%s\': not a valid identifier\n", s->bob->token[i]);
	}
	else
	{
		while (s->bob->token[i][j] != '=' && s->bob->token[i][j])
		{
			if (!ft_isalnum_(s->bob->token[i][j]))
			{
				g_errna = 1;
				printf("export: \'%s\': not a valid identifier\n", s->bob->token[i]);
			}
			j++;
		}
		if (s->bob->token[i][j] == '=' || !s->bob->token[i][j])
		{
			if (ft_checkdup(s, s->bob->token[i]) == 1)
				ft_lstadd_back(&s->env->next, ft_lstnew(s->bob->token[i]));
			g_errna = 0;
		}
	}
}

void	ft_export(t_struct *s)
{
	int		i;
	int		j;

	s->env =s->first;
	i = 1;
	j = 0;
	if (s->bob->token[1] == NULL)
		ft_lstsort_str(s);
	else
	{
		while (s->bob->token[i])
		{
			ft_exportall(s, i, j);
			i++;
		}
	}
}
