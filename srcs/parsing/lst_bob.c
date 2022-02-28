/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:51:07 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/28 13:47:42 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bob	*lastbob(t_bob *bob)
{
	if (!bob)
		return (0);
	while (bob->next)
		bob = bob->next;
	return (bob);
}

t_bob	*new_bob(void)
{
	t_bob	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (0);
	list->next = NULL;
	list->fd_in = 0;
	list->fd_out = 1;
	list->mode_out = 0;
	list->mode_in = 0;
	return (list);
}

/*
params	: la struct et l'input taper
return	: je sais pas encore///////////////////
def		: cree la liste chainer comportant les cmd de char ** les fd;/
*/

char	*one_token_for_bob(char *str)
{
	int		i;
	int		j;
	char	*a_token;

	i = 0;
	j = 0;
	a_token = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!a_token)
		return (NULL);
	while (str[i])
		add_char(a_token, str, &j, &i);
	a_token[j] = 0;
	return (a_token);
}

int	fct(char **str, int start, int end, t_struct *s)
{
	int	word;
	int	file_ret;

	file_ret = 0;
	s->bob = lastbob(s->bob);
	word = end - start + lst_ajustement(str, start, end);
	s->bob->token = malloc(sizeof(char *) * (word + 1));
	if (!s->bob->token)
		return (-1);
	word = 0;
	while (start < end)
	{
		if (ft_is_chevron(str[start][0]) && file_ret != -1)
			file_ret = gere_chevron(str, &start, s->bob, s);
		else if (ft_is_chevron(str[start][0]))
			start++;
		else
		{
			s->bob->token[word] = one_token_for_bob(str[start]);
			word++;
		}
		start++;
	}
	s->bob->token[word] = 0;
	return (0);
}

void	create_bob(char **str, t_struct *s)
{
	int		start;
	int		end;
	t_bob	*first_bob;

	start = 0;
	end = 0;
	s->bob = new_bob();
	first_bob = s->bob;
	while (str[end])
	{
		while (str[end] && str[end][0] != '|')
			end++;
		if (fct(str, start, end, s) == -1)
			return ;
		if (str[end] && str[end][0] == '|')
			end += 1;
		if (str[end])
		{
			s->bob->next = new_bob();
			s->bob = s->bob->next;
		}
		start = end;
	}
}
