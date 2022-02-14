#include "../../includes/minishell.h"
#include <stdbool.h>

void ctrl_child(int n)
{
	(void)n;
	printf("\n");
	g_errna = 130;
}

int ft_exec(t_struct *s, char *str)
{
	int fd_in;
	int fd_out;
	int i;
	int status;

	i = 0;
	fd_in = -1;
	fd_out = -1;
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (is_first_builtin(s, fd_in, fd_out) == 1)
			;
		else
			ft_fork_exec(s, &fd_in, &fd_out);
		i++;
	}
	i = 0;
	while (i < s->no_pipe + 1)
	{
		tcsetattr(0, TCSANOW, &s->old_termios);
		waitpid(s->data.id1[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status) == true)
		printf("\n");
	g_errna = WEXITSTATUS(status);
	s->env = s->first;
	return (0);
}
