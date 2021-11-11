/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:08:37 by elabasqu          #+#    #+#             */
/*   Updated: 2021/03/20 16:33:57 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	int		i;

	i = -1;
	tab = malloc(size * nmemb);
	if (!(tab))
		return (NULL);
	ft_bzero(tab, size * nmemb);
	return (tab);
}
