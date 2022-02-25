/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:25:50 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/25 15:09:55 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c(int n)
{
	(void)n;
	g_errna = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(t_struct *s)
{
	tcgetattr(0, &s->old_termios);
	tcgetattr(0, &s->new_termios);
	s->new_termios.c_lflag &= ~ECHOCTL;
	s->new_termios.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &s->new_termios);
	signal(SIGINT, ctrl_c);
}

void	ctrl_child(int n)
{
	(void)n;
	printf("\n");
	g_errna = 130;
}

void	ctrl_quit(int n)
{
	(void)n;
	g_errna = 131;
}

void	sig_airdog(int n)
{
	(void)n;
	printf("\n");
	g_errna = 1;
	exit(g_errna);
}
