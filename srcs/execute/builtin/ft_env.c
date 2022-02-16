/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:47 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/16 13:29:48 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_env(t_struct *s)
{
	if (s->bob->token[1] != NULL)
	{
		g_errna = 1;
		printf("env: Invalid number of arguments\n");
		exit(1);
	}
	s->env = s->first;
	while (s->env->next != NULL)
	{
		if (ft_strchr(s->env->content, '=') != NULL)
			printf("%s\n", s->env->content);
		s->env = s->env->next;
	}
	if (ft_strchr(s->env->content, '=') != NULL)
		printf("%s\n", s->env->content);
	g_errna = 0;
}	
