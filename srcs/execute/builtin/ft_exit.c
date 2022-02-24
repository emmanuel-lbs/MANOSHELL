/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:50 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/24 15:47:19 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_checkdigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1])
		i++;
	if (str[i] >= 20)
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

static void	ft_print_exit(t_struct *s, char *str, int error)
{
	tcsetattr(0, TCSANOW, &s->old_termios);
	printf("%s\n", str);
	g_errna = error;
	exit(error);
}

static void	ft_print_noexit(t_struct *s, char *str, int error)
{
	tcsetattr(0, TCSANOW, &s->old_termios);
	printf("%s\n", str);
	g_errna = error;
}

void	ft_exit(t_struct *s)
{
	if (s->bob->token[1] == NULL)
		ft_print_exit(s, "exit ", g_errna);
	else if (s->bob->token[1] && s->bob->token[2] != NULL)
		ft_print_noexit(s, "exit: too many arguments", 1);
	else if (ft_checkdigit(s->bob->token[1]) == -1)
		ft_print_exit(s, "exit: numeric argument required", 2);
	else
		ft_print_exit(s, "exit ", ft_atoi(s->bob->token[1]));
}

void	ft_pipexit(t_struct *s)
{
	if (s->bob->token[1] && s->bob->token[2] != NULL)
		ft_print_noexit(s, "exit: too many arguments", 1);
	else if (ft_checkdigit(s->bob->token[1]) == -1)
		ft_print_noexit(s, "exit: numeric argument required", 255);
	else
		g_errna = ft_atoi(s->bob->token[1]);
}
