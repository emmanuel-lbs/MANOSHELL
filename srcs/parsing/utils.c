/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:11 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/21 14:01:30 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_is_builtin(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	token_len(char *cmd, int i)
{
	while (cmd[i] && cmd[i] != ' ' \
			&& ft_is_chevron(cmd[i]) == 0 && cmd[i] != '|' && cmd[i] != '$')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"' )
			skip_quote(cmd, cmd[i], &i);
		else
			i++;
	}
	return (i);
}

void	printf_lst(t_bob *bob)
{
	int	i;

	while (bob != NULL)
	{
		i = 0;
		while (bob->token[i])
		{
			printf(" -%s- ", bob->token[i]);
			i++;
		}
		printf("out = %d in = %d", bob->fd_out, bob->fd_in);
		printf("mode in = %d, heredocs = \n", bob->mode_in);
		printf("\n");
		bob = bob->next;
	}
}
