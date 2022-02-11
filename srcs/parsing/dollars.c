/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:07:04 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/11 14:58:23 by elabasqu         ###   ########lyon.fr   */
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
			if (ft_strncmp(dollars, s->env->content, len_env(dollars)) == 0)
				return (1);
		s->env = s->env->next;
	}
	if (s->env->content)
		if (ft_strncmp(dollars, s->env->content, len_env(dollars)) == 0)
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

int	not_a_dollar(char *cmd, int i)
{
	i++;
	if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
		return (0);
	return (1);
}

char	*fake_dollars(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;

	j = *i;
	(*i)++;
	while (cmd[*i] && cmd[*i] != ' ' \
			&& ft_is_chevron(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"' )
			skip_quote(cmd, cmd[*i], i);
		else
			(*i)++;
	}
	a_token = malloc(sizeof(char) * (*i - j + 10));
	if (a_token == NULL)
		return (NULL);
	*i = j;
	j = 0;
	add_char(a_token, cmd, &j, i);
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 \
			&& ft_is_quote(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
		add_char(a_token, cmd, &j, i);
	if (cmd[*i] != '$' && ft_is_quote(cmd[*i]) == 1)
		cpy_quote(a_token, cmd, &j, i, s);
	a_token[j] = 0;
	if (cmd[*i] == '$')
		return (fusion_double_token(a_token, cmd, i, s));
	return (a_token);
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
	if (cmd[*i] != 0 && cmd[*i] != ' ' && (verif_quote(cmd, *i) == 0 \
				|| cmd[*i] == '$' || cmd[*i] == '/'))
		a_token = fusion_double_token(a_token, cmd, i, s);
	return (a_token);
}
