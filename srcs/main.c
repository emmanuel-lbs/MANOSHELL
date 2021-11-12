/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:11:11 by elabasqu          #+#    #+#             */
/*   Updated: 2021/11/12 11:01:06 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include "../includes/structure.h"


int	main(int ac, char **av, char **envp)
{
	char		*str;
	int			i;
	t_struct	s;

	i = 0;
	str = "";
	ft_check_path(&s.data, envp);
	while (s.data.env_path[i])
	{
		printf("data = %s\n", s.data.env_path[i]);
		i++;
	}
	while (1)
	{
		//On stocke le stdin dans str,
		//on peut changer ça en le mettant dans une struct au besoin.
		str = readline("MANULL le sang$ ");
		printf("%s\n",str);
		if (str == NULL)
			break;
		if (parsing)
		{
			exec
		}
		dprintf(1, "%d\n", ft_countwords(str));;
	}
}
