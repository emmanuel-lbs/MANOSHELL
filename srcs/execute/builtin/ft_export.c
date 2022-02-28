/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:55 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/28 14:25:20 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_exportoken(t_struct *s, int i, int *n)
{
	if (ft_checkdup(s, s->bob->token[i]) == 1)
		ft_lstadd_back(&s->env->next,
			ft_lstnew(ft_strdup(s->bob->token[i])));
	if (n == 0)
		g_errna = 0;
}

static void	ft_exportall(t_struct *s, int i, int j, int *n)
{
	if (!ft_isalpha_(s->bob->token[i][0]))
	{
		g_errna = 1;
		*n = 1;
		printf("export: \'%s\': not a valid identifier\n", s->bob->token[i]);
	}
	else
	{
		while (s->bob->token[i][j] != '=' && s->bob->token[i][j])
		{
			if (!ft_isalnum_(s->bob->token[i][j]))
			{
				g_errna = 1;
				*n = 1;
				printf("export: \'%s\': not a valid identifier\n",
					s->bob->token[i]);
				return ;
			}
			j++;
		}
		if (s->bob->token[i][j] == '=' || !s->bob->token[i][j])
			ft_exportoken(s, i, n);
	}
}

void	ft_export(t_struct *s)
{
	int		i;
	int		j;
	int		n;

	s->env = s->first;
	i = 1;
	j = 0;
	n = 0;
	if (s->bob->token[1] == NULL)
		ft_lstsort_str(s);
	else
	{
		while (s->bob->token[i])
		{
			ft_exportall(s, i, j, &n);
			i++;
		}
	}
}
