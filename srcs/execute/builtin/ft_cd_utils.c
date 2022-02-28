/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:00:39 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/28 11:01:04 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_do_cd(t_struct *s, int *status, char *pwd)
{
	char	*tmp1;
	char	*tmp2;

	*status = 1;
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

void	ft_putenv(t_struct *s)
{
	if (ft_strnncmp("PWD=", s->env->content, 3) == 0)
	{
		if (s->data.n == 1)
			free(s->env->content);
		s->env->content = ft_strdup(s->pwd.content);
	}
	else if (ft_strnncmp("OLDPWD=", s->env->content, 6) == 0)
	{
		if (s->data.n == 1)
			free(s->env->content);
		s->env->content = ft_strdup(s->old_pwd.content);
	}
}
