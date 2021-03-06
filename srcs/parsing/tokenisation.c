/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:25:02 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/03 11:34:24 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 *
 * params	: la commande
 * return	: le nb de token
 * def		: skipe les spaces prend bien les quotes
 *			  ignore les chevron et nom des redirection
 *			  (">> lol" pas pris en compte)
 *			  norme rend degeu le else if et while devrais etre ensemble;
 */

int	size_of_token(char *cmd, int i)
{
	int	tmp;

	tmp = i;
	if (ft_is_chevron(cmd[i]) == 1)
	{
		if (ft_is_chevron(cmd[i + 1]) == 1)
			return (2);
		return (1);
	}
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"' )
		{
			skip_quote(cmd, cmd[i], &i);
			return (i - tmp);
		}
		else if (ft_is_chevron(cmd[i]) == 1)
			return (i - tmp);
		else
			i++;
	}
	return (i - tmp);
}

char	*fusion_double_token(char *str, char *cmd, int *i, t_struct *s)
{
	char	*dollars;
	char	*retur;

	dollars = one_token(cmd, i, s);
	retur = ft_strjoin(str, dollars);
	free(dollars);
	free(str);
	return (retur);
}

char	*normal_token(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;
	int		*norme[2];

	a_token = malloc(sizeof(char) * (token_len(cmd, *i) - *i + 1));
	if (a_token == NULL)
		return (NULL);
	j = 0;
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 \
			&& ft_is_quote(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
		add_char(a_token, cmd, &j, i);
	norme[0] = &j;
	norme[1] = i;
	a_token[j] = 0;
	if (cmd[*i] == '$' || ft_is_quote(cmd[*i]) == 1)
		return (ft_strjoinfree(a_token, one_token(cmd, i, s), 3));
	return (a_token);
}

char	*one_token(char *cmd, int *i, t_struct *s)
{
	char	*a_token;

	if (ft_is_chevron(cmd[*i]) == 1)
		a_token = cpy_chevron(cmd, i);
	else if (ft_is_quote(cmd[*i]) == 1)
		a_token = one_token_quote(cmd, i, s);
	else if (cmd[*i] == '$' && last_carat(cmd, *i) == 0)
		a_token = one_token_dollars(cmd, i, s);
	else if (cmd[*i] == '$' && last_carat(cmd, *i) == 1)
		a_token = dollars_for_hered(cmd, i, s);
	else if (cmd[*i] == '|')
	{
		(*i)++;
		a_token = ft_strdup("|");
	}
	else
	{
		a_token = normal_token(cmd, i, s);
	}
	if (a_token == NULL)
		a_token = ft_strdup("");
	return (a_token);
}

char	**split_shell(char *cmd, t_struct *s)
{
	char	**token;
	int		i;
	int		word;

	token = malloc(sizeof(char *) * (wcount(cmd) + ajustement(cmd, s) + 1));
	if (token == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i])
		{
			token[word] = one_token(cmd, &i, s);
			if (token[word] != NULL && should_mod(cmd, i, token[word], s) != 0)
				modif_token(token[word], token, &word);
			word++;
		}
	}
	token[word] = 0;
	return (token);
}
