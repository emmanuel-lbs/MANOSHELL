/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:30:02 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/18 12:20:34 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_redirect(t_bob *bob)
{
	ft_redir_close(bob->fd[0], 0);
	close(bob->fd[1]);
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
