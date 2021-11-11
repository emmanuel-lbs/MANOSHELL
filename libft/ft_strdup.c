/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:03:58 by elabasqu          #+#    #+#             */
/*   Updated: 2021/03/20 16:40:14 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*tab;
	int		i;
	int		len_src;

	len_src = ft_strlen(src);
	tab = malloc(sizeof(char) * (len_src + 1));
	if (!(tab))
	{
		tab = 0;
		return (tab);
	}
	i = 0;
	while (i < len_src)
	{
		tab[i] = src[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
