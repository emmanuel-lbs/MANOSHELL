/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:35:48 by elabasqu          #+#    #+#             */
/*   Updated: 2021/03/20 16:46:50 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_isline(const char *s, int i)
{
	if (!s)
		return (i);
	while (s[i])
	{
		if (s[i] == '\n')
			return (-1);
		i++;
	}
	return (i);
}

char	*ft_gnl_join(const char *s1, const char *s2)
{
	char	*concat;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	concat = malloc(sizeof(char) * (ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1));
	if (!(concat))
		return (NULL);
	while (++i < ft_gnl_strlen(s1))
		concat[i] = s1[i];
	while (++j < ft_gnl_strlen(s2))
		concat[i + j] = s2[j];
	concat[i + j] = 0;
	free((char *)s1);
	return (concat);
}

char	*ft_gnl_cpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src == 0)
		return (0);
	while (src[i] && i < size - 1)
	{
		if (size > 0)
		{
			dest[i] = src[i];
		}
		i++;
	}
	if (size > 0)
		dest[i] = 0;
	while (src[i])
		i++;
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if (len < 0)
		len *= -1;
	result = malloc(sizeof(char) * len + 1);
	if (result == NULL || s == 0)
		return (NULL);
	i = 0;
	if (start >= (unsigned int)ft_gnl_strlen(s))
	{
		result[i] = 0;
		return (result);
	}
	s += start;
	while (*s && i < len)
	{
		result[i] = *s;
		i++;
		s++;
	}
	result[i] = 0;
	return (result);
}
