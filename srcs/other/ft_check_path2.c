/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:24:35 by rozhou            #+#    #+#             */
/*   Updated: 2022/03/03 12:25:58 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_checkcd(t_struct *s)
{
	s->env->tofree = 0;
	if (ft_strncmp(s->env->content, "PWD=", 4) == 0)
		s->pwd = *s->env;
	else if (ft_strncmp(s->env->content, "OLDPWD", 6) == 0)
	{
		s->old_pwd = *s->env;
		s->old_pwd.content = NULL;
		s->env->content = "OLDPWD";
	}
	else if (ft_strncmp(s->env->content, "HOME=", 5) == 0)
		s->home = *s->env;
}
