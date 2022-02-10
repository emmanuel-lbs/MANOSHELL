/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:51:07 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/10 14:51:09 by elabasqu         ###   ########lyon.fr   */
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
	list->heredocs = NULL;
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

int	fct(char **str, int start, int end, t_bob *bob)
{
	int	word;
	int	file_ret;

	file_ret = 0;
	bob = lastbob(bob);
	word = end - start + lst_ajustement(str, start, end);
	bob->token = malloc(sizeof(char *) * (end - start + 1));
	if (!bob->token)
		return (-1);
	word = 0;
	while (start < end)
	{
		if (ft_is_chevron(str[start][0]) && file_ret != -1)
			file_ret = gere_chevron(str, &start, bob);
		else if (ft_is_chevron(str[start][0]) && str[start][1] != '<')
			start += 2;
		else
		{
			bob->token[word] = one_token_for_bob(str[start]);
			word++;
		}
		start++;
	}
	bob->token[word] = 0;
	if (bob->fd_in == -1)
		bob->fd_out = -1;
	return (0);
}

t_bob	*create_bob(char **str)
{
	t_bob	*bob;
	int		start;
	int		end;
	t_bob	*first_bob;

	start = 0;
	end = 0;
	bob = new_bob();
	first_bob = bob;
	while (str[end])
	{
		while (str[end] && str[end][0] != '|')
			end++;
		if (fct(str, start, end, bob) == -1)
			return (NULL);
		if (str[end] && str[end][0] == '|')
			end += 1;
		if (str[end])
		{
			bob->next = new_bob();
			bob = bob->next;
		}
		start = end;
	}
	return (first_bob);
}
