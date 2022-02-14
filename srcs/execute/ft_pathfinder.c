#include "../../includes/minishell.h"

static int	ft_checkfile_nopath(struct stat buf, t_struct *s)
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

static int	ft_checkfile(struct stat buf, t_struct *s)
{
	if (S_ISDIR(buf.st_mode))
	{
		printf("Command not found: %s\n", s->bob->token[0]);
		return (-1);
	}
	if (access(s->bob->token[0], X_OK) == 0)
		return (1);
	else
	{
		printf("Command not found: %s\n", s->bob->token[0]);
		g_errna = 127;
		return (-1);
	}
}

static void	ft_joincommands(t_struct *s)
{
	int n;

	n = 0;
	while (s->data.env_path[++n])
	{
		s->data.env_path[n] = ft_strjoin(s->data.env_path[n], "/");
		s->data.env_path[n] = ft_strjoin(s->data.env_path[n], s->bob->token[0]);
	}
}

int	ft_pathfinder(t_struct *s, int n)
{
	struct stat buf;

	stat(s->bob->token[0], &buf);
	if (s->data.env_path == NULL)
	{
		if (ft_checkfile(buf, s) == -1)
			return (-1);
		return (1);
	}
	else
	{
		ft_join_commands(s);
		while (access(s->data.env_path[n], F_OK) != 0 && s->data.env_path[n])
			n++;
		if (!s->data.env_path[n])
		{
			if (ft_checkfile(buf, s) == -1)
				return (-1);
			return (1);
		}
	}
	s->bob->token[0] = s->data.env_path[n];
	return (1);
}