/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:40 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/24 15:35:57 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_cd_home(t_struct *s)
{
	char	*pwd;
	char	*tmp1;
	char	*tmp2;

	pwd = NULL;
	if (chdir(s->home.content + 5))
	{
		if (!s->home.content)
		{
			g_errna = 1;
			printf("HOME not set\n");
		}
	}
	else
	{
		pwd = getcwd(pwd, 0);
		if (pwd)
		{
			tmp1 = s->old_pwd.content;
			s->old_pwd.content = s->pwd.content;
			tmp2 = s->pwd.content;
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
			if (s->data.n == 1)
			{
				free(tmp1);
				free(tmp2);
			}
		}
		g_errna = 0;
	}
}

static void	ft_cd_old(t_struct *s)
{
	char	*pwd;
	char	*tmp1;
	char	*tmp2;

	pwd = NULL;
	if (s->old_pwd.content == NULL)
	{
		g_errna = 1;
		printf("OLDPWD not set\n");
	}
	else if (chdir(s->old_pwd.content + 7))
	{
		g_errna = 1;
		printf("%s : No such file or directory\n", s->old_pwd.content + 7);
	}
	else
	{
		pwd = getcwd(pwd, 0);
		if (pwd)
		{
			tmp1 = s->old_pwd.content;
			s->old_pwd.content = s->pwd.content;
			tmp2 = s->pwd.content;
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
			if (s->data.n == 1)
			{
				free(tmp1);
				free(tmp2);
			}
		}
		g_errna = 0;
	}
}

static void	ft_cd_all(t_struct *s)
{
	char	*pwd;
	char	*tmp1;
	char	*tmp2;

	pwd = NULL;
	if (chdir(s->bob->token[1]))
	{
		g_errna = 1;
		printf("%s : No such file or directory\n", s->bob->token[1]);
	}
	else
	{
		pwd = getcwd(pwd, 0);
		if (pwd)
		{
			tmp1 = s->old_pwd.content;
			s->old_pwd.content = s->pwd.content;
			tmp2 = s->pwd.content;
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
			if (s->data.n == 1)
			{
				free(tmp1);
				free(tmp2);
			}
		}
		g_errna = 0;
	}
}

void	ft_cd(t_struct *s)
{
	char	*pwd;
	int		i;

	pwd = NULL;
	i = 0;
	if (!s->bob->token[1])
		ft_cd_home(s);
	else if (ft_strcmp(s->bob->token[1], "-") == 0)
		ft_cd_old(s);
	else
		ft_cd_all(s);
	while (s->env != NULL)
	{
		if (ft_strncmp("PWD=", s->env->content, 4) == 0)
		{
			if (s->data.n == 1)
				free(s->env->content);
			s->env->content = ft_strdup(s->pwd.content);
		}
		else if (ft_strncmp("OLDPWD=", s->env->content, 7) == 0)
		{
			if (s->data.n == 1)
				free(s->env->content);
			s->env->content = ft_strdup(s->old_pwd.content);
		}
		s->env = s->env->next;
	}
	s->env = s->first;
	s->data.n = 1;
}
