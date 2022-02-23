/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:06:06 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/23 14:21:03 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	how_many_token(char *s, int *i, int *nb)
{
	if (*i != 0 && s[(*i) - 1] != ' ' \
			&& (ft_is_chevron(s[*i]) == 1 || s[*i] == '|'))
		(*nb)++;
	if (s[*i] == '|' && (ft_is_quote(s[(*i) + 1]) == 1 \
				|| (s[(*i) + 1] != ' ' && ft_is_chevron(s[(*i) + 1]) == 0)))
		(*nb)++;
	if (s[*i] && ft_is_quote(s[*i]) == 1)
		skip_quote(s, s[*i], i);
	else if (s[*i] && ft_is_chevron(s[*i]) == 1)
	{
		while (s[*i] && ft_is_chevron(s[*i]) == 1)
			(*i)++;
		if (s[*i] && s[*i] != ' ')
			(*nb)++;
	}
	else
		(*i)++;
}

int	ajustement(char *s, t_struct *struc)
{
	int		i;
	int		nb;
	char	*a_token;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			a_token = one_token_dollars(s, &i, struc);
			if (a_token != NULL && a_token[0] != 0)
			{
				if (should_mod(s, i, a_token, struc) == 1)
					nb += 2;
				free(a_token);
			}
			else if (a_token != NULL && a_token[0] == 0)
				if (ft_isdigit(s[i]) == 1)
					nb += 1;
		}
		else
			i++;
	}
	return (nb);
}

int	wcount(char *s)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] && s[i] != ' ')
			nb++;
		while (s[i] && s[i] != ' ')
			how_many_token(s, &i, &nb);
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (nb);
}

int	should_mod(char *cmd, int i, char *a_token, t_struct *s)
{
	char	*first_word;

	if (is_first_word_and_dollars(cmd, i) == 0)
		return (0);
	first_word = first_word_fct(a_token);
	if (first_word == NULL)
		return (0);
	if (!(ft_is_builtin(first_word) == 1 || is_cmd(s, first_word) == 1))
	{
		free(first_word);
		return (0);
	}
	free(first_word);
	return (1);
}

void	modif_token(char *a_token, char **lst_tkn, int *nb_word)
{
	char	*first_word;

	first_word = first_word_fct(a_token);
	lst_tkn[*nb_word] = first_word;
	(*nb_word)++;
	lst_tkn[*nb_word] = next_token(a_token);
	free(a_token);
}
