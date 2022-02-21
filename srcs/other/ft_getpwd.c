#include "../../includes/minishell.h"

static void	ft_strcolor(t_struct *s, char **mem, int i)
{
	char	*freestr;

	if (g_errna != 0)
	{
		freestr = ft_strjoin(mem[i - 1], "\033[0m ");
		s->prompt = ft_strjoin("\033[0;31m➜ \033[1;36m", freestr);
	}
	else
	{
		freestr = ft_strjoin(mem[i - 1], "\033[0m ");
		s->prompt = ft_strjoin("\033[0;32m➜ \033[1;36m", freestr);
	}
	free(freestr);
}

void	ft_get_pwd(t_struct *s, char *pwd)
{
	int		i;
	char	**mem;

	mem = ft_split((pwd), '/');
	i = 0;
	while (mem[i])
		i++;
	if (i == 1)
	{
		mem[0][0] = '/';
		mem[0][1] = '\0';
	}
	ft_strcolor(s, mem, i);
	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	s->env = s->first->next;
	free(mem);
}
