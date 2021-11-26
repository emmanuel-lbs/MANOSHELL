
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
	s->first = s->env;
	while (s->env.next != NULL)
	{
		s->env = *s->env.next;
		if (ft_strncmp(s->env.content, "PWD=", 4) == 0)
			s->pwd = s->env;
		else if (ft_strncmp(s->env.content, "OLDPWD=", 7) == 0)
			s->old_pwd = s->env;
		else if (ft_strncmp(s->env.content, "HOME=", 5) == 0)
			s->home = s->env;
	}
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	s->data.env_path = ft_split((envp[i]), ':');
	s->data.env_path[0] = (s->data.env_path[0] + 5);
	return (1);
}
