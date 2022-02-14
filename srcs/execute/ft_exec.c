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
	int to_close;
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
		{
			if (pipe(s->data.end) == -1)
			{
				g_errna = errno;
				printf("Pipe error\n");
				return (0);
			}
			to_close = s->data.end[0];
			signal(SIGINT, SIG_IGN);
			s->data.id1[i] = fork();
			if (s->data.id1[i] == -1)
			{
				g_errna = errno;
				printf("Fork error\n");
				return (-1);
			}
			if (s->data.id1[i] == 0)
			{
				if (to_close)
					close(to_close);
				if (ft_pathfinder(s, -1) == -1)
					exit(127);
				if (fd_in)
				{
					dup2(fd_in, 0);
					close(fd_in);
				}
				if (s->bob->next != NULL)
				{
					dup2(s->data.end[1], 1);
					close(s->data.end[1]);
				}
				ft_redirect(s->bob, fd_in);
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
			if (fd_in)
				close(fd_in);
			fd_in = s->data.end[0];
			close(s->data.end[1]);
			s->bob = s->bob->next;
		}
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
