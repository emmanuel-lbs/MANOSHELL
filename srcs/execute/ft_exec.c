
#include "../../includes/minishell.h"

static int	ft_pathfinder(t_struct *s, int n)
{
	if (!s->data.env_path)
	{
		printf("Command not found: %s\n", s->bob->token[0]);
		return (-1);
	}
	else
	{
		if (access(*s->bob->token, F_OK) == 0)
			return (1);
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
			printf("Command not found: %s\n", s->bob->token[0]);
			return (-1);
		}
		s->bob->token[0] = s->data.env_path[n];
	}
	return (1);
}

int	ft_exec(t_struct *s, char *str)
{
	int	fd_in;

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
		else if (strcmp(s->bob->token[0], "lst") == 0 && !s->bob->next)
		{
			s->env = s->first;
			while (s->env->next != NULL)
			{
				printf(" %s\n", s->env->content);
				s->env = s->env->next;
			}
			printf(" %s\n", s->env->content);
			usleep(500000);
		}
		else
		{
			if (pipe(s->data.end) == -1)
			{
				printf("Pipe error\n");
				return (0);
			}
			s->data.id1 = fork();
			if (s->data.id1 == -1)
			{
				printf("Fork error\n");
				return (-1);
			}
			if (s->data.id1 == 0)
			{	
				//On change l'input avec l'ancient
				dup2(fd_in, 0);
				if (s->bob->next != NULL)
					dup2(s->data.end[1], 1);
				close(s->data.end[0]);
				if (is_builtin(s) == 0)
				{
					if (ft_pathfinder(s, -1) == -1)
						exit(EXIT_SUCCESS);
					execve(s->bob->token[0], s->bob->token, s->data.envp);
				}
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(s->data.id1, 0, 0);
				close(s->data.end[1]);
				//on sauvegarde l'input pour le donner au prochain pipe
				fd_in = s->data.end[0];
				s->bob = s->bob->next;
			}
		}
	}
	s->env = s->first;
	return (0); //37 lignes Fonction erreur pour gagner 6 lignes
}
