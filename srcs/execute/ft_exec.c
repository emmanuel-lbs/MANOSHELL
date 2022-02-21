/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:29:59 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/21 14:18:22 by rozhou           ###   ########.fr       */
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

int	ft_exec(t_struct *s, int i, int status, int builtin)
{
	int	fd_in;

	fd_in = -1;
	s->data.id1 = malloc(sizeof(int) * s->no_pipe + 1);
	tcsetattr(0, TCSANOW, &s->old_termios);
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (!s->bob->token[0][0])
		{
			printf("Command not found: \n");
			s->bob = s->bob->next;
			g_errna = 1;
		}
		else if (is_first_builtin(s, i) == 1)
			builtin = 1;
		else
			ft_fork_exec(s, &fd_in, i);
		i++;
	}
	ft_check_exit(s, status, builtin);
	if (s->data.end[0])
		close(s->data.end[0]);
	s->env = s->first;
	return (0);
}
