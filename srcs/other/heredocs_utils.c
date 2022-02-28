/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:11:14 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/28 13:34:01 by elabasqu         ###   ########lyon.fr   */
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
