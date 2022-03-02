/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:45:20 by elabasqu          #+#    #+#             */
/*   Updated: 2022/03/02 18:33:13 by elabasqu         ###   ########lyon.fr   */
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

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*heredocs(char	*end_word, t_struct *s)
{
	char	*str;
	char	*hered;

	str = readline("<<");
	if (str == 0 || strcmp(str, end_word) == 0)
	{
		hered = ft_strdup("");
		free(str);
		return (hered);
	}
	if (is_dollar(str) == 1)
		str = dollars_hered(str, s);
	hered = ft_strjoinfree(str, "\n", 1);
	while (1)
	{
		str = readline("<<");
		if (str == 0 || strcmp(str, end_word) == 0)
			return (hered);
		if (is_dollar(str) == 1)
			str = dollars_hered(str, s);
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

//rajouter la struct partout pour one token
