#include "../../includes/minishell.h"

static int	ft_print_error(char *str, int error)
{
	g_errna = error;
	printf("%s\n", str);
	return (-1);
}

void	ft_fork_exec(t_struct *s, int *fd_in, int *fd_out)
{
	int to_close;

	if (pipe(s->data.end) == -1)
		return (ft_print_error("Pipe error\n", errno));
	to_close = s->data.end[0];
	signal(SIGINT, SIG_IGN);
	s->data.id1[i] = fork();
	if (s->data.id1[i] == -1)
		return (ft_print_error("Fork error\n", errno));
	if (s->data.id1[i] == 0)
	{
		if (to_close)
			close(to_close);
		if (ft_pathfinder(s, -1) == -1)
			exit(127);
		if (*fd_in)
			ft_redir_close(*fd_in, 0);
		if (s->bob->next != NULL)
			ft_redir_close(s->data.end[1], 1);
		ft_redirect(s->bob, *fd_in);
		if (is_builtin(s) == 0)
		{
			g_errna = 0;
			tcsetattr(0, TCSANOW, &s->old_termios);
			signal(SIGINT, ctrl_child);
			execve(s->bob->token[0], s->bob->token, s->data.envp);
			exit(1);
		}
		exit(g_errna);
	}
	if *fd_in)
        close(*fd_in);
	*fd_in = s->data.end[0];
	close(s->data.end[1]);
	s->bob = s->bob->next;
}