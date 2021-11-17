
#include "../../includes/minishell.h"

static int	ft_pathfinder(t_struct *s, int n)
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
		printf("Command not found: %s\n", s->bob->token[0]);
		return (-1);
	}
	s->bob->token[0] = s->data.env_path[n];
	return (1);
}

int	ft_exec(t_struct *s)
{
	// ################## On attends bob du parsing ####################################

	t_bob	bob;

	s->bob = &bob;
	s->bob->token = ft_split("ls -l", ' ');

	// ################## IL EST LA bob du parsing ####################################

	s->data.id1 = fork();
	if (s->data.id1 == -1)
	{
		printf("Fork error\n");
		return (-1);
	}
	if (s->data.id1 == 0)
	{
		if (ft_pathfinder(s, -1) == -1)
			exit(EXIT_SUCCESS);
		execve(s->bob->token[0], s->bob->token, s->data.envp);
		exit(EXIT_SUCCESS);
	}
	printf("END\n");
	return (0);
}
