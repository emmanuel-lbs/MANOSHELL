/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:11 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/18 12:01:00 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char(char *cpy, char *str, int *i, int *j)
{
		cpy[*i] = str[*j];
		(*i)++;
		(*j)++;
}

int	ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_is_chevron(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	skip_quote(char *s, char quote, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
			(*i)++;
	if (s[*i] != quote)
	{
		printf("missing one quote\n");
		return (-1);
	}
	(*i)++;
	if (s[*i] && ft_is_quote(s[*i]) == 1)
		if (skip_quote(s, s[*i], i) == -1)
			return (-1);
	while (s[*i] && s[*i] != ' ' && ft_is_quote(s[*i]) == 0 \
			&& ft_is_chevron(s[*i]) == 0 && s[*i] != '|')
		(*i)++;
	if (s[*i] && ft_is_quote(s[*i]) == 1)
		if (skip_quote(s, s[*i], i) == -1)
			return (-1);
	return (0);
}

void	printf_lst(t_bob *bob)
{
	int i;
	while (bob != NULL)
	{
		i = 0;
		while (bob->token[i])
		{
			printf(" -%s- ",bob->token[i]);
			i++;
		}
		printf("out = %d in = %d", bob->fd_out, bob->fd_in);
		printf("mode in = %d, heredocs = \n",bob->mode_in);
		printf("\n");
		bob = bob->next;
	}
}

