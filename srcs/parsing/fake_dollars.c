/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:28:06 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/21 14:01:55 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_a_dollar(char *cmd, int i)
{
	i++;
	if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_' && cmd[i] != '?')
		return (0);
	return (1);
}

char	*fake_dollars(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;

	(*i)++;
	a_token = malloc(sizeof(char) * (token_len(cmd, *i) - *i));
	if (a_token == NULL)
		return (NULL);
	(*i)--;
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

char	*dollars_erno(char **a_token, int *i)
{
	char	*retur;

	free(*a_token);
	(*i)++;
	retur = ft_itoa(g_errna);
	return (retur);
}
