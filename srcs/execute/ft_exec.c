#include "../../includes/minishell.h"
#include <stdbool.h>

static void	ft_check_exit(t_struct *s, int status)
{
	int i;

	i = 0;
	while (i < s->no_pipe + 1)
	{
		waitpid(s->data.id1[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status) == true)
		printf("\n");
	g_errna = WEXITSTATUS(status);
}

int ft_exec(t_struct *s, char *str, int i)
{
	int fd_in;
	int fd_out;
	int status;

	fd_in = -1;
	fd_out = -1;
	tcsetattr(0, TCSANOW, &s->old_termios);
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (is_first_builtin(s, fd_in, fd_out) == 1)
			;
		else
			ft_fork_exec(s, &fd_in, &fd_out, i);
		i++;
	}
	ft_check_exit(s, status);
	s->env = s->first;
	return (0);
}
