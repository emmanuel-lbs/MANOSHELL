/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:30:06 by rozhou            #+#    #+#             */
/*   Updated: 2022/02/18 13:30:17 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_struct *s)
{
	if (strcmp(s->bob->token[0], "cd") == 0)
		ft_cd(s);
	else if (ft_strcmp(s->bob->token[0], "echo") == 0)
		ft_echo(s);
	else if (strcmp(s->bob->token[0], "pwd") == 0)
		ft_pwd();
	else if (strcmp(s->bob->token[0], "export") == 0)
		ft_export(s);
	else if (strcmp(s->bob->token[0], "unset") == 0)
		ft_unset(s);
	else if (strcmp(s->bob->token[0], "env") == 0)
		ft_env(s);
	else if (strcmp(s->bob->token[0], "exit") == 0)
		ft_pipexit(s);
	else
		return (0);
	return (1);
}

static int	ft_redirect_builtins(t_struct *s, void (*builtin)(t_struct *))
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	ft_redirect(s->bob);
	(*builtin)(s);
	ft_redir_close(fd_in, 0);
	ft_redir_close(fd_out, 1);
	s->bob = s->bob->next;
	return (1);
}

int	is_first_builtin(t_struct *s, int i)
{
	if (strcmp(s->bob->token[0], "cd") == 0 && i == 0 && !s->bob->next)
		return (ft_redirect_builtins(s, &ft_cd));
	else if (strcmp(s->bob->token[0], "export") == 0 && i == 0 && !s->bob->next)
		return (ft_redirect_builtins(s, &ft_export));
	else if (strcmp(s->bob->token[0], "unset") == 0 && i == 0 && !s->bob->next)
		return (ft_redirect_builtins(s, &ft_unset));
	else if (strcmp(s->bob->token[0], "exit") == 0 && i == 0 && !s->bob->next)
		return (ft_redirect_builtins(s, &ft_exit));
	else
		return (0);
	return (1);
}
