/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:59 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/17 13:13:24 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

static void	ft_check_exit(t_struct *s, int status, int builtin)
{
	int	i;

	i = 0;
	while (i < s->no_pipe + 1)
	{
		waitpid(s->data.id1[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status) == true)
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_errna = 130;
			printf("\n");
		}
	}
	else
		if (WIFEXITED(status) && builtin == 0)
			g_errna = WEXITSTATUS(status);
}

int	ft_exec(t_struct *s, int i)
{
	int	fd_in;
	int	fd_out;
	int	status;
	int	builtin;

	fd_in = -1;
	fd_out = -1;
	status = 0;
	builtin = 0;
	tcsetattr(0, TCSANOW, &s->old_termios);
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (is_first_builtin(s, i) == 1)
			builtin = 1;
		else
			ft_fork_exec(s, &fd_in, i);
		i++;
	}
	ft_check_exit(s, status, builtin);
	s->env = s->first;
	return (0);
}
