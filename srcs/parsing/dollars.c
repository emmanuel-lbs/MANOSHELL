/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:07:04 by elabasqu          #+#    #+#             */
/*   Updated: 2022/01/27 14:17:08 by rozhou           ###   ########.fr       */
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

int	search_dollars(char *dollars, t_struct *s)
{
	s->env = s->first;
	while (s->env->next != NULL)
	{
		if (s->env->content)
			if (ft_strncmp(dollars, s->env->content, len_env((char *)s->env->content)) == 0)
				return (1);
		s->env = s->env->next;
	}
	if (s->env->content)
		if (ft_strncmp(dollars, s->env->content, len_env((char *)s->env->content)) == 0)
			return (1);
	s->env = s->first;
	return (-1);
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

char	*dollars_num(char *cmd)
{
	int		i;
	char	*token;

	i = 0;
	while (ft_isdigit(cmd[i]) == 1)
		i++;
	token = malloc(sizeof(char) * (i + 1));
	if (token == NULL)
		return (NULL);
	i = 0;
	while (ft_isdigit(cmd[i]) == 1)
	{
		token[i] = cmd[i];
		i++;
	}
	token[i] = 0;
	return (token);
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
	while (ft_isalnum(cmd[*i]) == 1)
		(*i)++;
	token = malloc(sizeof(char) * (*i - ret + 1));
	if (token == NULL)
		return (NULL);
	*i = ret;
	ret = 0;
	while (cmd[*i] != 0 && ft_isalnum(cmd[*i]) == 1)
	{
		add_char(token, cmd, &ret, i);
	}
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
	if (search_dollars(a_token, s) == -1)
		return (NULL);
	a_token = change_dollars(a_token, s->env->content);
	if (a_token == NULL)
		return (NULL);
	if (cmd[*i] != 0 && cmd[*i] != ' ' && (verif_quote(cmd, *i) == 0 || cmd[*i] == '$'))
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
	char	*dollars;

	diff = 0;
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
		else
			start++;
	}
	while (cmd[start] && start <= end && cmd[start] != ' ')
		start++;
	return (diff);
}
