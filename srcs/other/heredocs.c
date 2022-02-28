
#include "../../includes/minishell.h"

t_bob	*heredocs_bob(t_bob *bob)
{
	int	i;

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
	return (bob);
}

char	*modif_here_dol(char *str, char *dollars, t_struct *s)
{
	int		i;
	int		j;
	int		k;
	char	*newstr;

	j = 0;
	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(dollars)));
	while (str[i])
	{
		if (str[i] == '$')
		{
			k = 0;
			while (dollars[k])
				add_char(newstr, dollars, &j, &k);
			free(one_token(str, &i, s));
		}
		else
			add_char(newstr, str, &j, &i);
	}
	newstr[j] = 0;
	return (newstr);
}

void	dollars_hered(char *str, t_struct *s)
{
	int		i;
	char	*dollars;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollars = one_token(str, &i, s);
			new_str = modif_here_dol(str, dollars, s);
		}
		else
			i++;
	}
}

char	*heredocs(char	*end_word, t_struct *s)
{
	char	*str;
	char	*hered;

	str = readline("<<");
	dollars_hered(str, s);
	if (str == 0 || strcmp(str, end_word) == 0)
	{
		hered = ft_strdup("");
		free(str);
		return (hered);
	}
	hered = ft_strjoinfree(str, "\n", 1);
	while (1)
	{
		str = readline("<<");
		//dollars_hered(str);
		if (str == 0 || strcmp(str, end_word) == 0)
			return (hered);
		hered = ft_strjoinfree(hered, str, 3);
		hered = ft_strjoinfree(hered, "\n", 1);
	}
	return (hered);
}

static void	child_airdog(char *end_word, int *fd, t_struct *s)
{
	char	*hered;

	signal(SIGINT, &sig_airdog);
	hered = heredocs(end_word, s);
	ft_putstr_fd(hered, fd[1]);
	ft_redir_close(fd[1], 1);
	free(hered);
	close(fd[0]);
	exit(0);
}

int	second_airdog(t_bob *bob, char *end_word, t_struct *s)
{
	int		pid;
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		printf("Pipe error\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Pid error\n");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		child_airdog(end_word, fd, s);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_errna = WEXITSTATUS(status);
	bob->fd[0] = fd[0];
	bob->fd[1] = fd[1];
	return (0);
}

void	beging_hered(char **str, int actual_word, t_bob *bob, t_struct *s)
{
	second_airdog(bob, heredocs_end_word(str, actual_word), s);
}

//rajouter la struct partout pour one token
