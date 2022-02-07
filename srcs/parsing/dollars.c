/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:14 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/07 11:42:57 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:07:04 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/07 11:32:37 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_env(char *env)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

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
			quote =  cmd[j];
			j++;
			while (j < i && cmd[j] && cmd[j] != quote)
				j++;
			if (j < i && cmd[j] == quote)
			{
				j++;
				pair++;
			}
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
			if (ft_strncmp(dollars, s->env->content, len_env((char *)dollars)) == 0)
				return (1);
		s->env = s->env->next;
	}
	if (s->env->content)
		if (ft_strncmp(dollars, s->env->content, len_env((char *)dollars)) == 0)
			return (1);
	s->env = s->first;
	return (-1);
}

int	last_caractr(char *var)
{
	int i;

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
//	if (dollars[0] == '?')
		//
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

char *dollar_not_interpret(char *cmd, int *i)
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
	while (cmd[*i] != 0 && (ft_isalnum(cmd[*i]) == 1))
		add_char(token, cmd, &ret, i);
	token[ret] = 0;
	return (token);
}

char	*one_token_dollars(char *cmd, int *i, t_struct *s)
{
	char	*a_token;

	a_token = dollar_not_interpret(cmd, i);
	if (a_token == NULL)
		return (NULL);
	if (a_token[0] == 0)
		return (a_token);
	if (a_token[0] == '?')
	{
		free(a_token);
		(*i)++;
		a_token = ft_itoa(g_errna);
		return (a_token);
	}
	if (search_dollars(a_token, s) == -1)
		return (NULL);
	if (where_dollar(cmd, *i) == 1)
		a_token = change_dollars(a_token, s->env->content);
	else
		a_token = change_dollars_no_space(a_token, s->env->content);
	if (a_token == NULL)
		return (NULL);
	if (cmd[*i] != 0 && cmd[*i] != ' ' && (verif_quote(cmd, *i) == 0 || cmd[*i] == '$' || cmd[*i] == '/'))
		a_token = fusion_double_token(a_token, cmd, i, s);
	return (a_token);
}
/*
 * ligne 79 return (dollars_num(&cmd[*i])); :
 * c'est faux ca nan si $8795478654 alors juste $8 skip je crois*/


int	diff_in_var_env(char *var)
{
	int i;
	int firstlen;
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

int	resize_len_for_dollar(char *cmd, int start, int end, t_struct *s)
{
	int		diff;
	char	quote;

	diff = 0;
	printf("%s\n",&cmd[end]);
	while (/*cmd[start] != quote &&*/ start < end)
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
