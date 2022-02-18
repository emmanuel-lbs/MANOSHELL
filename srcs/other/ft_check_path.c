/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:02:57 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/18 12:52:07 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Initialisation de la structure Data et environnement
//PWD=/Users/rozhou/42_Cursus/MANOSHELL
//SHLVL=1
//_=/Users/rozhou/42_Cursus/MANOSHELL/./MANOSHELL
static void	ft_create_env(t_struct *s)
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
	s->home.content = NULL;
	s->data.env_path = NULL;
}

static void	ft_shlvl(t_struct *s)
{
	s->env->content = ft_strjoin("SHLVL=",
			ft_itoa(ft_atoi(s->env->content + 6) + 1));
}

static void	ft_setenv(t_struct *s)
{
	while (s->env->next != NULL)
	{
		if (ft_strncmp(s->env->content, "PWD=", 4) == 0)
			s->pwd = *s->env;
		if (ft_strncmp(s->env->content, "SHLVL=", 6) == 0)
			ft_shlvl(s);
		else if (ft_strncmp(s->env->content, "OLDPWD", 6) == 0)
		{
				s->old_pwd = *s->env;
				s->old_pwd.content = NULL;
		}
		else if (ft_strncmp(s->env->content, "HOME=", 5) == 0)
				s->home = *s->env;
		s->env = s->env->next;
	}
	if (ft_strncmp(s->env->content, "PWD=", 4) == 0)
			s->pwd = *s->env;
	else if (ft_strncmp(s->env->content, "OLDPWD", 6) == 0)
	{
			s->old_pwd = *s->env;
			s->old_pwd.content = NULL;
	}
	else if (ft_strncmp(s->env->content, "HOME=", 5) == 0)
			s->home = *s->env;
}

static void	ft_setup_data(t_struct *s, int ac, char **av, char **envp)
{
	s->data.av = av;
	s->data.ac = ac;
	if (envp[0] == NULL)
		ft_create_env(s);
	else
		s->data.envp = envp;
}

int	ft_check_path(t_struct *s, char **envp, int ac, char **av)
{
	int	i;

	ft_setup_data(s, ac, av, envp);
	if (s->env)
		ft_lstprint(s->env);
	s->env = ft_lstnew(s->data.envp[0]);
	i = 1;
	while (s->data.envp[i])
	{
		ft_lstadd_back(&s->env->next, ft_lstnew(s->data.envp[i]));
		i++;
	}
	s->first = s->env;
	ft_setenv(s);
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
