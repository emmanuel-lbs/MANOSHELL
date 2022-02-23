/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:36:25 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/23 12:21:41 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*jpp_norme(const char *start, const char *s)
{
	char	*tab;

	tab = malloc(sizeof(char) * (s - start + 1));
	if (!(tab))
		return (NULL);
	ft_strlcpy(tab, start, s - start + 1);
	return (tab);
}

static int	ft_countword(const char *s, char c)
{
	int	nb;

	nb = 0;
	while (*s)
	{
		if (*s && *s != c && (*(s + 1) == c || *(s + 1) == 0))
			nb++;
		s++;
	}
	return (nb);
}

char	**ft_free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	const char	*start;
	char		**tab;

	i = 0;
	tab = ft_calloc(sizeof(char *), (ft_countword(s, c) + 1));
	if (!(tab))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		if (s != start)
		{
			tab[i] = jpp_norme(start, s);
			if (!tab[i])
				return (ft_free_split(tab));
			if (start != s)
				i++;
		}
	}
	return (tab);
}

char	**ft_splitone(char const *s, char c, int one)
{
	const char	*start;
	char		**tab;
	int			i;

	i = 0;
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
		if (s != start)
		{
			tab[i] = jpp_norme(start, s);
			one = 1;
			if (!tab[i])
			{
				return (ft_free_split(tab));
			}
			if (start != s)
				i++;
		}
	}
	return (tab);
}
