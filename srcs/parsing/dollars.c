/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:07:04 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/03 11:16:20 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	where_dollar(char *cmd, int i)
{
	int		j;
	char	quote;
	int		pair;

	j = 0;
	pair = 0;
	while (cmd[j] && j < i)
	{
		while (j < i && cmd[j] && ft_is_quote(cmd[j]) == 0)
			j++;
		if (cmd[j] && j < i && ft_is_quote(cmd[j]) == 1)
		{
			pair++;
			quote = cmd[j];
			j++;
			while (j < i && cmd[j] && cmd[j] != quote)
				j++;
			if (j < i && cmd[j] == quote)
				pair++;
			if (j < i && cmd[j] == quote)
				j++;
		}
	}
	pair = pair % 2;
	return (pair);
}

int	search_dollars(char *dollars, t_struct *s)
{
	s->env = s->first;
	while (s->env->next != NULL)
	{
		if (s->env->content)
			if (ft_strnncmp(dollars, s->env->content, len_env(dollars)) == 0)
				return (1);
		s->env = s->env->next;
	}
	if (s->env->content)
		if (ft_strnncmp(dollars, s->env->content, len_env(dollars)) == 0)
			return (1);
	s->env = s->first;
	return (-1);
}

int	strlen_var_env_no_space(char *var)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (var[i] && var[i] != '=')
		i++;
	i++;
	while (var[i])
	{
		while (var[i] && var[i] != ' ')
		{
			i++;
			ret++;
		}
		if (var[i] && var[i] == ' ' && i < last_caractr(var))
			ret++;
		while (var[i] && var[i] == ' ')
			i++;
	}
	return (ret);
}

char	*dollar_not_interpret(char *cmd, int *i)
{
	int		ret;
	char	*token;

	(*i)++;
	ret = *i;
	if (ft_isdigit(cmd[*i]) == 1)
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (cmd[*i] == '?')
		return (ft_strdup("?"));
	while (ft_isalnum(cmd[*i]) == 1 || cmd[*i] == '_')
		(*i)++;
	token = malloc(sizeof(char) * (*i - ret + 1));
	if (token == NULL)
		return (NULL);
	*i = ret;
	ret = 0;
	while (cmd[*i] != 0 && ((ft_isalnum(cmd[*i]) == 1) || cmd[*i] == '_'))
		add_char(token, cmd, &ret, i);
	token[ret] = 0;
	return (token);
}

char	*one_token_dollars(char *cmd, int *i, t_struct *s)
{
	char	*a_token;

	if (not_a_dollar(cmd, *i) == 0)
		return (fake_dollars(cmd, i, s));
	a_token = dollar_not_interpret(cmd, i);
	if (a_token == NULL || a_token[0] == 0)
		return (a_token);
	if (a_token[0] == '?')
		return (dollars_erno(&a_token, i));
	if (search_dollars(a_token, s) == -1)
	{
		free(a_token);
		return (NULL);
	}
	if (where_dollar(cmd, *i) == 1)
		a_token = change_dollars(a_token, s->env->content);
	else
		a_token = change_dollars_no_space(a_token, s->env->content);
	if (a_token == NULL)
		return (NULL);
	if (cmd[*i] != 0 && cmd[*i] != ' ' && (verif_quote(cmd, *i) == 0 \
				|| cmd[*i] == '$' || cmd[*i] == '/' || cmd[*i] == '='))
		a_token = ft_strjoinfree(a_token, one_token(cmd, i, s), 3);
	return (a_token);
}
