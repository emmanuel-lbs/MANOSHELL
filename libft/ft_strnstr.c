/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:11:07 by elabasqu          #+#    #+#             */
/*   Updated: 2020/12/10 09:14:14 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(n[i]))
		return ((char *)h);
	while (i < len && h[i])
	{
		j = 0;
		if (h[i] == n[j])
		{
			while (h[i + j] == n[j] && i + j < len && h[i + j] && n[j])
				j++;
		}
		if (!(n[j]))
			return ((char *)&h[i]);
		i++;
	}
	return (0);
}
