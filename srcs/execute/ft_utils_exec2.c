#include "../../includes/minishell.h"

void    ft_setenv_null(t_struct *s)
{
	if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
		s->old_pwd.content = NULL;
	else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
		s->data.env_path = NULL;
	else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
		s->home.content = NULL;
}

int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}


int	ft_strccmp(const char *s1, const char *s2, char c)
{
	int			i;
	int			min;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	min = -1;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (ss1[i] != '\0')
	{
		if (ss1[i] == c)
		{
			min = i;
			break ;
		}
		i++;
	}
	i = 0;
	while (ss2[i] != '\0')
	{
		if (ss2[i] == c)
		{
			if (i > min)
				min = i;
			break ;
		}
		i++;
	}
	i = 0;
	while ((ss1[i] != '\0' || ss2[i] != '\0') && i < min)
	{
		if (ss1[i] - ss2[i] != 0)
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (min == -1)
	{
		while ((ss1[i] != '\0' || ss2[i] != '\0'))
		{
			if (ss1[i] - ss2[i] != 0)
				return (ss1[i] - ss2[i]);
			i++;
		}
	}
	return (0);
}

int	ft_strgetchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}