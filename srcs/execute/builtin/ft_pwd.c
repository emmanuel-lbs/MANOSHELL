/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:56 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/16 13:29:57 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (str)
		printf("%s\n", str);
	free(str);
	g_errna = 0;
}
