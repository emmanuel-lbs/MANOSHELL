#include "../../includes/minishell.h"

static int	ft_pathfinder(t_struct *s, int n)
{
	struct stat	buf;

	stat(s->bob->token[0], &buf);
	if (s->data.env_path == NULL)
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("%s: is a directory\n", s->bob->token[0]);
			g_errna = 126;
			return (-1);
		}
		else if (access(s->bob->token[0], F_OK) != 0)
		{
			printf("%s: No such file or directory\n", s->bob->token[0]);
			g_errna = 127;
			return (-1);			
		}
		else if (access(s->bob->token[0], X_OK) == 0)
			return (1);
		else
		{
			printf("%s: Permission denied\n", s->bob->token[0]);
			g_errna = 126;
			return (-1);
		}
	}
	else
	{
		while (s->data.env_path[++n])
		{	
			s->data.env_path[n] = ft_strjoin(s->data.env_path[n], "/");
			s->data.env_path[n] = ft_strjoin(s->data.env_path[n], s->bob->token[0]);
		}
		n = 0;
		while (access(s->data.env_path[n], F_OK) != 0 && s->data.env_path[n])
			n++;
		if (!s->data.env_path[n])
		{
			/*if (S_ISDIR(buf.st_mode))
			{
				printf("Command not found: %s\n", s->bob->token[0]);
				return (-1);
			}*/
			if (access(s->bob->token[0], X_OK) == 0)
				return (1);
			else
			{
				printf("Command not found: %s\n", s->bob->token[0]);
				g_errna = 127;
				return (-1);
			}
		}
	}
	s->bob->token[0] = s->data.env_path[n];
	return (1);
}

void	ft_redirect(t_bob *bob, int	fd_in)
{
	int	fd[2];
	int	pid;
	int	to_close;

	if (bob->mode_in == 2)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_putstr_fd(bob->heredocs, fd[1]);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else if (bob->fd_in != 0)
	{
		dup2(bob->fd_in, 0);
		close(bob->fd_in);
	}
	if (bob->fd_out != 1)
	{
		dup2(bob->fd_out, 1);
		close(bob->fd_out);
	}
}

int	ft_exec(t_struct *s, char *str)
{
	int	fd_in;
	int	fd_out;
	int	to_close;
	int	i;
	int	status;

	i = 0;
	fd_in = -1;
	fd_out = -1;
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (strcmp(s->bob->token[0], "cd") == 0 && i == 0 && !s->bob->next)
		{
			fd_in = dup(0);
			fd_out = dup(1);
			ft_redirect(s->bob, 0);
			ft_cd(s);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			close(fd_in);
			close(fd_out);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "export") == 0 && i == 0 && !s->bob->next)
		{
			fd_in = dup(0);
			fd_out = dup(1);
			ft_redirect(s->bob, 0);
			ft_export(s);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			close(fd_in);
			close(fd_out);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "unset") == 0 && i == 0 && !s->bob->next)
		{
			fd_in = dup(0);
			fd_out = dup(1);
			ft_redirect(s->bob, 0);
			ft_unset(s);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			close(fd_in);
			close(fd_out);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "exit") == 0 && i == 0 && !s->bob->next)
		{
			fd_in = dup(0);
			fd_out = dup(1);
			ft_redirect(s->bob, 0);
			printf("exit \n");
			ft_exit(s);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			close(fd_in);
			close(fd_out);
			s->bob = s->bob->next;
		}
/*								EXEC PIPE																*/
		else
		{
			if (pipe(s->data.end) == -1)
			{
				g_errna = errno;
				printf("Pipe error\n");
				return (0);
			}
			to_close = s->data.end[0];
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
					execve(s->bob->token[0], s->bob->token, s->data.envp);
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
	while(i < s->no_pipe + 1)
	{
		waitpid(s->data.id1[i], &status, 0);
		i++;
	}
	g_errna = WEXITSTATUS(status);
	s->env = s->first;
	return (0); //37 lignes Fonction erreur pour gagner 6 lignes
}
