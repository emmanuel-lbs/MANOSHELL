/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <elabasqu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:47:08 by elabasqu          #+#    #+#             */
/*   Updated: 2021/03/20 16:34:55 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_int(int a)
{
	int			i;
	long int	n;

	n = a;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int a)
{
	char		*str;
	long int	n;
	int			i;

	n = a;
	i = ft_strlen_int(n);
	str = malloc(sizeof(char) * (ft_strlen_int(n) + 1));
	if (!(str))
		return (NULL);
	str[i--] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		str[i--] = n % 10 + 48;
		n /= 10;
	}
	str[i] = n % 10 + 48;
	return (str);
}
