/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:53:50 by elabasqu          #+#    #+#             */
/*   Updated: 2020/11/30 10:53:46 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*sdest;
	unsigned char	*ssrc;
	size_t			i;

	i = -1;
	sdest = (unsigned char *)dest;
	ssrc = (unsigned char *)src;
	if (sdest == 0 && ssrc == 0)
		return (NULL);
	while (++i < n)
		sdest[i] = ssrc[i];
	return (dest);
}
