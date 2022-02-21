/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:45:38 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/21 15:39:04 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cpy_quote(char *cpy, char *cmd, int *n[2], t_struct *s)
{
	char	quote;

	quote = cmd[*n[1]];
	if (cpy_quote_avant(cpy, cmd, n, s) == -1)
		return (-1);
	(*n[1])++;
	if (cmd[*n[1]] && ft_is_quote(cmd[*n[1]]) == 1)
		cpy_quote(cpy, cmd, n, s);
	if (cmd[*n[1]] && cmd[*n[1]] == '$')
		if (dollar_in_quote(cpy, cmd, n, s) == -1)
			return (-1);
	while (cmd[*n[1]] && cmd[*n[1]] != ' ' && ft_is_chevron(cmd[*n[1]]) == 0 \
			&& ft_is_quote(cmd[*n[1]]) == 0 && cmd[*n[1]] != '|')
		add_char(cpy, cmd, n[0], n[1]);
	if (cmd[*n[1]] && ft_is_quote(cmd[*n[1]]) == 1)
		cpy_quote(cpy, cmd, n, s);
	cpy[*n[0]] = 0;
	return (0);
}

int	verif_quote(char *cmd, int i)
{
	int		j;
	char	quote;

	j = 0;
	if (ft_is_quote(cmd[i]) != 1)
		return (-1);
	while (cmd[j] && j < i)
	{
		while (cmd[j] && ft_is_quote(cmd[j]) == 0)
			j++;
		if (j == i)
			return (0);
		quote = cmd[j];
		j++;
		while (cmd[j] && cmd[j] != quote)
			j++;
		if (j < i)
			j++;
	}
	if (j == i)
		return (1);
	return (-1);
}

int	number_of_quote(char *cmd, int start, int end)
{
	char	quote;
	int		nb_quote;

	nb_quote = 0;
	while (start < end)
	{
		if (ft_is_quote(cmd[start]) == 1)
		{
			quote = cmd[start];
			start++;
			nb_quote += 2;
			while (cmd[start] != quote)
				start++;
			start++;
		}
		else
			start++;
	}
	return (nb_quote);
}

char	*one_token_quote(char *cmd, int *i, t_struct *s)
{
	char	*a_token;
	int		start;
	int		end;
	int		*norme[2];

	start = *i;
	skip_quote(cmd, cmd[*i], i);
	end = *i;
	*i += resize_len_for_dollar(cmd, start, end, s);
	*i -= number_of_quote(cmd, start, end);
	a_token = malloc(sizeof(char) * (*i - start + 1));
	if (a_token == NULL)
		return (NULL);
	*i = start;
	start = 0;
	norme[0] = &start;
	norme[1] = i;
	if (cpy_quote(a_token, cmd, norme, s) == -1)
		return (NULL);
	return (a_token);
}
