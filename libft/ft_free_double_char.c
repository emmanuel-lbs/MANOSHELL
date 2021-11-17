/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:03:54 by elabasqu          #+#    #+#             */
/*   Updated: 2021/11/17 15:36:18 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_double_char(char **str)
{
	int	i;

	i = -1;
	(void)str;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}
