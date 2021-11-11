/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:33:00 by rozhou            #+#    #+#             */
/*   Updated: 2021/11/11 15:50:21 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structure.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_data	data;
	int		i;

	i = 0;
	str = "";
	ft_check_path(&data, envp);
	while (data.env_path[i])
	{
		printf("data = %s\n", data.env_path[i]);
		i++;
	}
	while (str != NULL)
	{
		//On stocke le stdin dans str, 
		//on peut changer ça en le mettant dans une struct au besoin.
		str = readline("MANULL le sang$ ");
	}
}