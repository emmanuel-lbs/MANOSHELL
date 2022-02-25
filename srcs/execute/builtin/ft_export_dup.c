/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:51 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/24 15:05:46 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_checkalldup(t_struct *s, char *str)
{
	if (ft_strccmp(s->env->content, str, '=', 0) == 0)
	{
		if (ft_strgetchar(str, '=') == 1)
		{
			if (ft_strncmp(str, "PATH=", 5) == 0)
			{
				s->data.env_path = ft_split((str), ':');
				s->data.env_path[0] = (s->data.env_path[0] + 5);
			}
			else if (ft_strncmp(str, "HOME=", 5) == 0)
			{
				printf("str = %s\n", str);
				s->home.content = str;
			}
			s->env->content = str;
		}
		return (0);
	}
	return (1);
}

static int	ft_checkequal(t_struct *s, char *str)
{
	if (ft_strccmp(s->env->content, str, '=', 0) == 0)
	{
		if (ft_strgetchar(str, '=') == 1)
		{
			if (ft_strncmp(str, "PATH=", 5) == 0)
			{
				s->data.env_path = ft_split((str), ':');
				s->data.env_path[0] = (s->data.env_path[0] + 5);
			}
			else if (ft_strncmp(str, "HOME=", 5) == 0)
				s->home.content = str;
			s->env->content = str;
		}
		return (0);
	}
	return (1);
}

static void	ft_setenv(t_struct *s, char *strdup)
{
	if (ft_strncmp(strdup, "PATH=", 5) == 0)
	{
		s->data.env_path = ft_split((strdup), ':');
		s->data.env_path[0] = (s->data.env_path[0] + 5);
	}
	else if (ft_strncmp(strdup, "HOME=", 5) == 0)
		s->home.content = strdup;
}

int	ft_checkdup(t_struct *s, char *str)
{
	char	*strdup;

	strdup = ft_strdup(str);
	s->env = s->first;
	while (s->env->next != NULL)
	{
		if (ft_strccmp(s->env->content, strdup, '=', 0) == 0)
		{
			if (ft_checkalldup(s, strdup) == 0)
			{
				free(strdup);
				return (0);
			}
		}
		s->env = s->env->next;
	}
	if (ft_checkequal(s, strdup) == 0)
	{	
		free(strdup);
		return (0);
	}
	ft_setenv(s, strdup);
	free(strdup);
	return (1);
}
