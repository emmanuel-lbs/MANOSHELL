/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:59 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/16 14:13:39 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

static void	ft_check_exit(t_struct *s, int status)
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
			printf("\n");
	}
	if (WIFEXITED(status))
		g_errna = WEXITSTATUS(status);
}

int	ft_exec(t_struct *s, int i)
{
	int	fd_in;
	int	fd_out;
	int	status;

	fd_in = -1;
	fd_out = -1;
	status = 0;
	tcsetattr(0, TCSANOW, &s->old_termios);
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (is_first_builtin(s, i) == 1)
			;
		else
			ft_fork_exec(s, &fd_in, i);
		i++;
	}
	ft_check_exit(s, status);
	s->env = s->first;
	return (0);
}
