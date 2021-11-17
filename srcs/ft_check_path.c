
#include "../includes/minishell.h"

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
	while (s->env.next != NULL)
	{
		printf("env = %s\n", s->env.content);
		s->env = *s->env.next;
	}
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	s->data.env_path = ft_split((envp[i]), ':');
	s->data.env_path[0] = (s->data.env_path[0] + 5);
	return (1);
}
