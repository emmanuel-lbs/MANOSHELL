/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   again_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:16:18 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/23 13:45:12 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_dollars_no_space(char *dollars, char *var)
{
	int		i;
	int		j;
	char	*a_token;

	i = 0;
	j = 0;
	a_token = malloc(sizeof(char) * (strlen_var_env_no_space(var) + 1));
	while (var[i] && var[i] != '=')
		i++;
	i++;
	while (var[i])
	{
		while (var[i] && var[i] != ' ')
			add_char(a_token, var, &j, &i);
		if (var[i] && var[i] == ' ' && i < last_caractr(var))
			add_char(a_token, var, &j, &i);
		while (var[i] && var[i] == ' ')
			i++;
	}
	a_token[j] = 0;
	free(dollars);
	return (a_token);
}

char	*change_dollars(char *dollars, char *var)
{
	int		i;
	int		j;
	char	*a_token;

	i = 0;
	j = 0;
	a_token = malloc(sizeof(char) * (strlen_var_env(var) + 1));
	while (var[i] && var[i] != '=')
		i++;
	if (var[i])
		i++;
	while (var[i])
		add_char(a_token, var, &j, &i);
	a_token[j] = 0;
	free(dollars);
	return (a_token);
}

int	resize_len_for_dollar(char *cmd, int start, int end, t_struct *s)
{
	int		diff;
	char	quote;

	diff = 0;
	while (start < end)
	{
		if (ft_is_quote(cmd[start]) == 1)
		{
			quote = cmd[start];
			start++;
			while (cmd[start] && cmd[start] != quote)
			{
				if (cmd[start] == '$' && quote != '\'')
					diff += search_diff(cmd, &start, s);
				else
					start++;
			}
			start++;
		}
		if (cmd[start] == '$' && quote != '\'')
			diff += search_diff(cmd, &start, s);
		else
			start++;
	}
	return (diff);
}
