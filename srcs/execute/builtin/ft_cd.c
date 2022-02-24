/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:40 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/24 12:51:54 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_cd_home(t_struct *s)
{
	char	*pwd;

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
			if (s->data.n == 1 && ft_strcmp(s->pwd.content, s->old_pwd.content) != 0)
				free(s->old_pwd.content);
			s->old_pwd.content = s->pwd.content;
			if (s->data.n == 1)
				free(s->pwd.content);
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
		}
		g_errna = 0;
	}
}

static void	ft_cd_old(t_struct *s)
{
	char	*pwd;

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
			if (s->data.n == 1)
				free(s->old_pwd.content);
			s->old_pwd.content = s->pwd.content;
			if (s->data.n == 1)
				free(s->pwd.content);
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
		}
		g_errna = 0;
	}
}

static void	ft_cd_all(t_struct *s)
{
	char	*pwd;

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
			if (s->data.n == 1)
				free(s->old_pwd.content);
			s->old_pwd.content = s->pwd.content;
			if (s->data.n == 1)
				free(s->pwd.content);
			s->pwd.content = pwd;
			s->pwd.content = ft_strjoinfree("PWD=", s->pwd.content, 2);
			s->old_pwd.content = ft_strjoin("OLD", s->old_pwd.content);
		}
		g_errna = 0;
	}
}

void	ft_cd(t_struct *s)
{
	char	*pwd;

	pwd = NULL;
	if (!s->bob->token[1])
		ft_cd_home(s);
	else if (ft_strcmp(s->bob->token[1], "-") == 0)
		ft_cd_old(s);
	else
		ft_cd_all(s);
	s->data.n = 1;
}
