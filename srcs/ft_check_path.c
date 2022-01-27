
#include "../includes/minishell.h"

//Initialisation de la structure Data et environnement
//PWD=/Users/rozhou/42_Cursus/MANOSHELL
//SHLVL=1
//_=/Users/rozhou/42_Cursus/MANOSHELL/./MANOSHELL
void	ft_create_env(t_struct *s)
{
	char	*str;

	str = NULL;
	s->data.envp = malloc(sizeof(char **) * 5);
	str = getcwd(str, 0);
	s->data.envp[0] = ft_strjoin("PWD=", str);
	s->data.envp[1] = ft_strjoin("SHLVL=", "1");
	s->data.envp[2] = ft_strjoin("_=", "/Users/rozhou/42_Cursus/MANOSHELL/./MANOSHELL");
	s->data.envp[3] = ft_strjoin("OLDPWD", "");
	s->data.envp[4] = NULL;

}

int	ft_check_path(t_struct *s, char **envp, int ac, char **av)
{
	int	i;

	s->data.av = av;
	s->data.ac = ac;
	if (envp[0] == NULL)
		ft_create_env(s);
	else
		s->data.envp = envp;
	s->env = ft_lstnew(s->data.envp[0]);
	i = 1;
	while (s->data.envp[i])
	{
		ft_lstadd_back(&s->env->next, ft_lstnew(s->data.envp[i]));
		i++;
	}
	s->first = s->env;
	while (s->env->next != NULL)
	{
		if (ft_strncmp(s->env->content, "PWD=", 4) == 0)
		{
			printf("findpwd\n");
				s->pwd = s->env;
		}
		else if (ft_strncmp(s->env->content, "OLDPWD", 6) == 0)
				s->old_pwd = s->env;
		else if (ft_strncmp(s->env->content, "HOME=", 5) == 0)
				s->home = s->env;
		s->env = s->env->next;
	}
	if (ft_strncmp(s->env->content, "PWD=", 4) == 0)
	{
			s->pwd = s->env;
	}
	else if (ft_strncmp(s->env->content, "OLDPWD", 6) == 0)
			s->old_pwd = s->env;
	else if (ft_strncmp(s->env->content, "HOME=", 5) == 0)
			s->home = s->env;
	i = 0;
	while (s->data.envp[i] && ft_strncmp(s->data.envp[i], "PATH=", 5))
			i++;
	if (s->data.envp[i])
	{
			s->data.env_path = ft_split((s->data.envp[i]), ':');
			s->data.env_path[0] = (s->data.env_path[0] + 5);
	}
	return (1);
}
