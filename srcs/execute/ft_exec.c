#include "../../includes/minishell.h"

static int	ft_pathfinder(t_struct *s, int n)
{
	struct stat	buf;

	stat(s->bob->token[0], &buf);
	if (s->data.env_path == NULL)
	{
		printf("NO_PATH\n");
		if (S_ISDIR(buf.st_mode))
		{
			printf("%s: is a directory\n", s->bob->token[0]);
			return (-1);
		}
		else if (access(s->bob->token[0], X_OK) == 0)
			return (1);
		else if (access(s->bob->token[0], F_OK) != 0)
			printf("%s: No such file or directory\n", s->bob->token[0]);
		else
			printf("%s: Permission denied\n", s->bob->token[0]);
		return (-1);
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
			printf("check\n");
			if (S_ISDIR(buf.st_mode))
			{
				printf("Command not found: %s\n", s->bob->token[0]);
				return (-1);
			}
			else if (access(s->bob->token[0], X_OK) == 0)
				return (1);
			else
			{
				printf("Command not found: %s\n", s->bob->token[0]);
				return (-1);
			}
		}
	}
	s->bob->token[0] = s->data.env_path[n];
	return (1);
}
int		ft_is_heredocs(t_bob *bob)
{
	int	i;

	i = 0;
	while (bob->token[i])
	{
		if (ft_strcmp(bob->token[i], "<<") == 0)
			return (1);
		i++;
	}
	printf("No heredocs\n");
	return (0);
}
void	ft_redirect(t_bob *bob, t_struct *s)
{
	int	fd[2];
	int	pid;
	int	to_close;

	if (ft_is_heredocs(bob) == 1)
	{
		if (pipe(s->data.end) == -1)
		{
			printf("Pipe error\n");
			exit(0);
		}
		to_close = s->data.end[0];
		pid = fork();
		if (pid == -1)
		{
			printf("Fork error\n");
			exit(0);
		}
		if (pid == 0)
		{	
			if (to_close)
				close(to_close);
	//		ft_putstr_fd(s->heredocs, fd[1]);
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		waitpid(pid, 0, 0);
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
	int	to_close;
	int	i;

	i = 0;
	fd_in = -1;
	while (s->bob != NULL)
	{
		if (!s->bob->token[0])
			s->bob = s->bob->next;
		else if (strcmp(s->bob->token[0], "cd") == 0 && !s->bob->next)
		{
			ft_cd(s);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "export") == 0 && !s->bob->next)
		{
			ft_export(s);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "unset") == 0 && !s->bob->next)
		{
			ft_unset(s);
			s->bob = s->bob->next;
		}
		else if (strcmp(s->bob->token[0], "exit") == 0 && !s->bob->next)
		{
			ft_exit(s);
			s->bob = s->bob->next;
		}
		else
		{
			if (pipe(s->data.end) == -1)
			{
				printf("Pipe error\n");
				return (0);
			}
			to_close = s->data.end[0];
			s->data.id1[i] = fork();
			if (s->data.id1[i] == -1)
			{
				printf("Fork error\n");
				return (-1);
			}
			if (s->data.id1[i] == 0)
			{	
				if (to_close)
					close(to_close);
				//On change l'input avec l'ancient
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
				ft_redirect(s->bob, s);
				if (is_builtin(s) == 0)
				{
					if (ft_pathfinder(s, -1) == -1)
						exit(EXIT_SUCCESS);
					printf("before excve\n");
					execve(s->bob->token[0], s->bob->token, s->data.envp);
				}
				exit(EXIT_FAILURE);
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
		waitpid(s->data.id1[i], 0, 0);
		i++;
	}
	printf("after excve\n");
	s->env = s->first;
	return (0); //37 lignes Fonction erreur pour gagner 6 lignes
}
