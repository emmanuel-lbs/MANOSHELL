/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:51:11 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/17 13:12:59 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	gere_out(char **str, int *i, t_bob *bob)
{
	if (bob->fd_out != 1)
		close(bob->fd_out);
	if (!str[*i][1])
	{
		bob->fd_out = open(str[++(*i)], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		bob->mode_out = 1;
	}
	else
	{
		bob->fd_out = open(str[++(*i)], O_CREAT | O_WRONLY | O_APPEND, 0644);
		bob->mode_out = 2;
	}
}

void	gere_in(char **str, int *actual_word, t_bob *bob)
{
	if (bob->fd_in != 0)
		close(bob->fd_in);
	if (!str[*actual_word][1])
	{
		bob->mode_in = 1;
		bob->fd_in = open(str[++(*actual_word)], O_RDONLY);
	}
	else
	{
		beging_hered(str, *actual_word, bob);
		(*actual_word)++;
		bob->mode_in = 2;
	}
}

int	gere_chevron(char **str, int *actual_word, t_bob *bob)
{
	if (str[*actual_word][0] == '>')
		gere_out(str, actual_word, bob);
	else if (str[*actual_word][0] == '<')
		gere_in(str, actual_word, bob);
	if (bob->fd_in == -1 || bob->fd_out == -1)
		return (-1);
	return (0);
}

int	lst_ajustement(char **str, int start, int end)
{
	int	nb;

	nb = 0;
	while (start < end)
	{
		if (ft_is_chevron(str[start][0]) && str[start][1] != '<')
			nb -= 2;
		start++;
	}
	return (nb);
}

char	*cpy_chevron(char *cmd, int *i)
{
	char	*a_token;

	if (ft_is_chevron(cmd[*i]) == 1 && ft_is_chevron(cmd[(*i) + 1]) == 1)
	{
		if (cmd[*i] == '<')
			a_token = ft_strdup("<<");
		else
			a_token = ft_strdup(">>");
		(*i) += 2;
	}
	else
	{
		if (cmd[*i] == '<')
			a_token = ft_strdup("<");
		else
			a_token = ft_strdup(">");
		(*i)++;
	}
	return (a_token);
}
