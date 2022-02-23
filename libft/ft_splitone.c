/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:33:34 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/23 10:54:40 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*jpp_norme(const char *start, const char *s)
{
	char	*tab;

	tab = malloc(sizeof(char) * (s - start + 1));
	if (!(tab))
		return (NULL);
	ft_strlcpy(tab, start, s - start + 1);
	return (tab);
}

static int	ft_splitone2(char const *s, char const *start, int *one, char **tab)
{
	int	i;

	i = 0;
	if (s != start)
	{
		tab[i] = jpp_norme(start, s);
		*one = 1;
		if (!tab[i])
		{
			ft_free_split(tab);
			return (0);
		}
		if (start != s)
			i++;
	}
	return (1);
}

char	**ft_splitone(char const *s, char c, int one, char	**tab)
{
	const char	*start;

	tab = ft_calloc(sizeof(char *), (2 + 1));
	if (!(tab))
		return (NULL);
	while (*s)
	{
		if (one == 1)
		{
			start = ++s;
			while (*s)
				s++;
		}
		else
		{
			while (*s && *s == c)
				s++;
			start = s;
			while (*s && *s != c)
				s++;
		}
		if (ft_splitone2(s, start, &one, tab) != 1)
			return (NULL);
	}
	printf("tab = %s\n", tab[0]);
	return (tab);
}
