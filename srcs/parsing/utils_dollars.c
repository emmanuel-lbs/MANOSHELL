/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:16:21 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/10 14:47:18 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_diff(char *cmd, int *start, t_struct *s)
{
	char	*dollars;

	dollars = dollar_not_interpret(cmd, start);
	if (dollars == NULL)
		return (-1);
	if (dollars[0] != 0)
	{
		search_dollars(dollars, s);
		return (diff_in_var_env(s->env->content));
	}
	free (dollars);
	return (0);
}

int	diff_in_var_env(char *var)
{
	int	i;
	int	firstlen;
	int	secondlen;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	firstlen = i + 1;
	while (var[i])
		i++;
	secondlen = i - firstlen;
	return (secondlen - firstlen);
}

int	strlen_var_env(char *var)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (var[i] && var[i] != '=')
		i++;
	ret = i + 1;
	while (var[ret])
		ret++;
	return (ret - i + 1);
}

int	last_caractr(char *var)
{
	int	i;

	i = ft_strlen(var);
	while (ft_is_quote(var[i]) != 1)
		i--;
	i--;
	if (var[i] != ' ')
		return (ft_strlen(var));
	while (var[i] == ' ')
		i--;
	return (i);
}

int	len_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

