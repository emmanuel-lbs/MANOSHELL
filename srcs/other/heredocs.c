#include "../../includes/minishell.h"

int	is_heredocs(t_struct *s)
{
	int i;

	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		i = 0;
		while (s->bob->token[i])
		{
			if (s->bob->token[i][0] == '<' && s->bob->token[i][1] == '<')
			{
				s->bob = s->first_bob;
				return (1);
			}
			i++;
		}
		s->bob = s->bob->next;
	}
	s->bob = s->first_bob;
	return (0);
}

char	*heredocs_end_word(char	**token, int i)
{
	while (token[i] && strcmp("<<", token[i]) != 0)
		i++;
	if (token[i] && strcmp("<<", token[i]) != 0)
		return (NULL);
	return (token[i + 1]);
}

t_bob	*heredocs_bob(t_bob *bob)
{
	int i;

	while (bob != NULL)
	{
		i = 0;
		while (bob->token[i] && strcmp("<<", bob->token[i]) != 0)
			i++;
		if (bob->token[i] && strcmp("<<", bob->token[i]) == 0)
			return (bob);
		bob = bob->next;
	}
	printf("error\n");
	exit(-1);
	return (bob);;
}

void	sig_airdog(int n)
{
	(void)n;
	printf("\n");
	g_errna = 1;
	exit(g_errna);
}

void	heredocs(t_bob *bob, char	*end_word)
{
	char	*str;

	str = "";
	str = readline("<<");
	if (str == 0 || strcmp(str, end_word) == 0)
	{
		bob->heredocs = ft_strdup("");
		return ;
	}
	bob->heredocs = ft_strjoin(str, "\n");
	free(str);
	while (1)
	{
		str = readline("<<");
		if (str == 0 || strcmp(str, end_word) == 0)
			return ;
		bob->heredocs = ft_strjoin(bob->heredocs, str);
		bob->heredocs = ft_strjoin(bob->heredocs, "\n");
		free(str);
	}
}

int	second_airdog(t_bob *bob, char *end_word)
{
	int	pid;
	int		status;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("Pipe error\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Pid error\n");
		return (-1);;
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, &sig_airdog);
		heredocs(bob, end_word);
		ft_putstr_fd(bob->heredocs, fd[1]);
		ft_redir_close(fd[1], 1);
		exit(1);
	}
	//	exit(1);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

void	beging_hered(char **str, int actual_word, t_bob *bob)
{
	second_airdog(bob, heredocs_end_word(str, actual_word));
	//	if (g_error_number)
	//		return (-1);
	//	close(fd[0]);
	//	close(fd[1]);
	//	return (0);
}
