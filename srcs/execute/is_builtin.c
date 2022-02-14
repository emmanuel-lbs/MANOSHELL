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
}

static void	ft_redirect_builtins(t_struct *s, void (*builtin)(t_struct *))
{
	fd_in = dup(0);
	fd_out = dup(1);
	ft_redirect(s->bob, 0);
	(*builtin)(s);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
	s->bob = s->bob->next;
}

int	is_first_builtin(t_struct *s, int fd_in, int fd_out)
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
}