/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:27:38 by elabasqu          #+#    #+#             */
/*   Updated: 2021/06/19 14:27:40 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int base, int power)
{
	int	result;

	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	result = 1;
	while (power > 0)
	{
		result *= base;
		power--;
	}
	return (result);
}
