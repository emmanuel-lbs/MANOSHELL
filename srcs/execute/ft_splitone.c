/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:20:34 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/24 11:20:47 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*one_split_one(char *s, char c)
{
	char	*one;
	int		i;
	int		j;

	i = 0;
	j = 0;
	one = malloc(sizeof(char) * (len_jusque(s, c) + 1));
	if (one == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
		add_char(one, s, &j, &i);
	one[j] = 0;
	return (one);
}

char	**ft_splitone(char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = ft_calloc(sizeof(char *), (2 + 1));
	if (!(tab))
		return (NULL);
	tab[0] = one_split_one(s, c);
	tab[1] = malloc(sizeof(char) * (ft_strlen(s) - len_jusque(s, c) + 1));
	if (tab[1] == NULL)
		return (NULL);
	i = len_jusque(s, c);
	j = 0;
	while (s[i])
		add_char(tab[1], s, &j, &i);
	tab[1][j] = 0;
	tab[2] = 0;
	return (tab);
}
