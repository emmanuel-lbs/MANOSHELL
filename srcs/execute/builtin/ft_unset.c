/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:57 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/16 13:29:58 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_unset_all(t_struct *s, int i)
{
	if (ft_strncmp(s->env->content, s->bob->token[i],
			ft_strclen(s->env->content, '=')) == 0)
	{
		ft_setenv_null(s);
		s->first = s->first->next;
		ft_delfirst(&s->env);
		return (1);
	}
	if (ft_strncmp(s->env->next->content, s->bob->token[i],
			ft_strclen(s->env->next->content, '=')) == 0)
	{
		ft_setenv_null(s);
		ft_delone(&s->env);
		return (1);
	}
	else
	{
		if (ft_strcmp(s->env->next->content, s->bob->token[i]) == 0)
		{
			ft_setenv_null(s);
			ft_delone(&s->env);
			return (1);
		}
	}
	return (0);
}

static void	ft_unset2(t_struct *s, int i, int j)
{
	while (s->bob->token[i][j])
	{
		if (!ft_isalnum_(s->bob->token[i][j]))
		{
			g_errna = 1;
			printf("unset: \'%s\': not a valid identifier\n", s->bob->token[i]);
		}
		j++;
	}
	if (!s->bob->token[i][j])
	{
		while (s->env->next != NULL)
		{
			if (ft_unset_all(s, i) == 1)
			{
				g_errna = 0;
				break ;
			}
			s->env = s->env->next;
		}
	}
}

void	ft_unset(t_struct *s)
{
	int		i;
	int		j;

	s->env = s->first;
	i = 1;
	j = 0;
	while (s->bob->token[i] != NULL)
	{
		if (!ft_isalpha_(s->bob->token[i][0]))
		{
			g_errna = 1;
			printf("unset: \'%s\': not a valid identifier\n", s->bob->token[i]);
		}
		else
			ft_unset2(s, i, j);
		i++;
	}
}
