/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:11 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/03 13:30:20 by rozhou           ###   ########.fr       */
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
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
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

int	dollar_in_quote(char *cpy, char *cmd, int *norme[2], t_struct *s)
{
	char	*dollars;
	int		k;

	dollars = one_token(cmd, norme[1], s);
	if (dollars == NULL)
		return (-1);
	k = 0;
	while (dollars[k])
	{
		cpy[*norme[0]] = dollars[k];
		(*norme[0])++;
		k++;
	}
	cpy[*norme[0]] = 0;
	free(dollars);
	return (0);
}

int	cpy_quote_avant(char *cpy, char *cmd, int *n[2], t_struct *s)
{
	char	quote;

	quote = cmd[*n[1]];
	(*n[1])++;
	while (cmd[*n[1]] && cmd[*n[1]] != quote)
	{
		if (cmd[*n[1]] && cmd[*n[1]] == '$' && quote == '\"')
		{
			if (dollar_in_quote(cpy, cmd, n, s) == -1)
				return (-1);
		}
		else
			add_char(cpy, cmd, n[0], n[1]);
		cpy[*n[0] + 1] = 0;
	}
	return (1);
}
