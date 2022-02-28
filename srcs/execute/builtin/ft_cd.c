/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:40 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/28 11:00:58 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_cd_home(t_struct *s, int *status)
{
	char	*pwd;

	*status = 1;
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
		*status = 1;
		ft_do_cd(s, status, pwd);
	}
}

static void	ft_cd_old(t_struct *s, int *status)
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
		*status = 1;
		ft_do_cd(s, status, pwd);
	}
}

static void	ft_cd_all(t_struct *s, int *status)
{
	char	*pwd;

	*status = 1;
	pwd = NULL;
	if (chdir(s->bob->token[1]))
	{
		g_errna = 1;
		printf("%s : No such file or directory\n", s->bob->token[1]);
	}
	else
	{
		*status = 1;
		ft_do_cd(s, status, pwd);
	}
}

void	ft_cd(t_struct *s)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	if (!s->bob->token[1])
		ft_cd_home(s, &status);
	else if (ft_strcmp(s->bob->token[1], "-") == 0)
		ft_cd_old(s, &status);
	else
		ft_cd_all(s, &status);
	if (status == 1)
	{
		while (s->env != NULL)
		{
			ft_putenv(s);
			s->env = s->env->next;
		}
	}
	s->env = s->first;
	s->data.n = 1;
}
