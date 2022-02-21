/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:00:32 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/21 14:36:47 by rozhou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*heredocs(char	*end_word)
{
	char	*str;
	char	*hered;

	str = "";
	str = readline("<<");
	if (str == 0 || strcmp(str, end_word) == 0)
	{
		hered = ft_strdup("");
		return (hered);
	}
	hered = ft_strjoin(str, "\n");
	free(str);
	while (1)
	{
		str = readline("<<");
		if (str == 0 || strcmp(str, end_word) == 0)
			return (hered);
		hered = ft_strjoin(hered, str);
		hered = ft_strjoin(hered, "\n");
		free(str);
	}
	return (hered);
}

static void	child_airdog(char *end_word, int *fd)
{
	char	*hered;

	signal(SIGINT, &sig_airdog);
	hered = heredocs(end_word);
	ft_putstr_fd(hered, fd[1]);
	ft_redir_close(fd[1], 1);
	close(fd[0]);
	exit(0);
}

int	second_airdog(t_bob *bob, char *end_word)
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
		child_airdog(end_word, fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_errna = WEXITSTATUS(status);
	bob->fd[0] = fd[0];
	bob->fd[1] = fd[1];
	return (0);
}

void	beging_hered(char **str, int actual_word, t_bob *bob)
{
	second_airdog(bob, heredocs_end_word(str, actual_word));
}
