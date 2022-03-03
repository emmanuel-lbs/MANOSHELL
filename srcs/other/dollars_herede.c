/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_herede.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:42:55 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/03 12:29:36 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fusion_double_tok_her(char *str, char *cmd, int *i, t_struct *s)
{
	char	*dollars;
	char	*retur;

	dollars = dollars_for_hered(cmd, i, s);
	retur = ft_strjoin(str, dollars);
	free(dollars);
	free(str);
	return (retur);
}

int	last_carat(char *cmd, int i)
{
	i--;
	while (i > 0 && cmd[i] == ' ')
		i--;
	if (ft_is_chevron(cmd[i]) == 1)
		return (1);
	return (0);
}

char	*dollars_for_hered(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;
	int		*norme[2];

	(*i)++;
	a_token = malloc(sizeof(char) * (token_len(cmd, *i)));
	if (a_token == NULL)
		return (NULL);
	(*i)--;
	j = 0;
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 \
			&& ft_is_quote(cmd[*i]) == 0 && cmd[*i] != '|')
		add_char(a_token, cmd, &j, i);
	norme[0] = &j;
	norme[1] = i;
	if (cmd[*i] != '$' && ft_is_quote(cmd[*i]) == 1)
		cpy_quote(a_token, cmd, norme, s);
	a_token[j] = 0;
	if (cmd[*i] == '$')
		return (fusion_double_tok_her(a_token, cmd, i, s));
	return (a_token);
}
