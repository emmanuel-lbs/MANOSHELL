
#include "../includes/minishell.h"

static void	ft_get_pwd(t_struct *s, char **envp)
{
	int		i;
	char	**mem;

	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4))
		i++;
	mem = ft_split((envp[i]), '/');
	i = 0;
	while (mem[i])
		i++;
	s->prompt = ft_strjoin(mem[i - 1], " :");
	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

//Initialisation de la structure Data et environnement
int	ft_check_path(t_struct *s, char **envp, int ac, char **av)
{
	int	i;

	i = 0;
	s->data.av = av;
	s->data.ac = ac;
	s->data.envp = envp;
	while (envp[i])
	{
		ft_lstadd_back(&s->env.next, ft_lstnew(envp[i]));
		i++;
	}
	s->first = s->env;
	while (s->env.next != NULL)
	{
		s->env = *s->env.next;
		if (ft_strncmp(s->env.content, "PWD=", 4))
			s->pwd = s->env;
	}
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	s->data.env_path = ft_split((envp[i]), ':');
	s->data.env_path[0] = (s->data.env_path[0] + 5);
	return (1);
}
