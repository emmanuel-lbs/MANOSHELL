/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:30:02 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/18 12:02:06 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_redirect(t_bob *bob)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
//		ft_putstr_fd(bob->heredocs, fd[1]);
		ft_redir_close(fd[1], 1);
		close(fd[0]);
		exit(0);
	}
	ft_redir_close(fd[0], 0);
	close(fd[1]);
}

void	ft_redirect(t_bob *bob, int fd_in)
{
	if (bob->mode_in == 2)
		ft_heredoc_redirect(bob);
	else if (bob->fd_in != 0)
		ft_redir_close(bob->fd_in, 0);
	if (bob->fd_out != 1)
		ft_redir_close(bob->fd_out, 1);
}
