/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:11:14 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/03 12:59:22 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredocs(t_struct *s)
{
	int	i;

	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		i = 0;
		while (s->bob->token[i])
		{
			if (s->bob->token[i][0] == '<' && s->bob->token[i][1] == '<')
			{
				s->bob = s->first_bob;
				return (1);
			}
			i++;
		}
		s->bob = s->bob->next;
	}
	s->bob = s->first_bob;
	return (0);
}

char	*heredocs_end_word(char	**token, int i)
{
	while (token[i] && strcmp("<<", token[i]) != 0)
		i++;
	if (token[i] && strcmp("<<", token[i]) != 0)
		return (NULL);
	return (token[i + 1]);
}

char	*modif_here_dol(char *str, char *dollars, t_struct *s, int k)
{
	int		i;
	int		j;
	char	*newstr;

	j = 0;
	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(dollars)));
	while (str[i])
	{
		if (str[i] == '$')
		{
			k = 0;
			while (dollars[k])
				add_char(newstr, dollars, &j, &k);
			free(one_token(str, &i, s));
			break ;
		}
		else
			add_char(newstr, str, &j, &i);
	}
	while (str[i])
		add_char(newstr, str, &j, &i);
	newstr[j] = 0;
	free(str);
	return (newstr);
}

char	*dollars_hered(char *str, t_struct *s)
{
	int		i;
	char	*dollars;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollars = one_token(str, &i, s);
			str = modif_here_dol(str, dollars, s, 0);
			free(dollars);
		}
		else
			i++;
	}
	return (str);
}
