/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_first_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elabasqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:11:37 by elabasqu          #+#    #+#             */
/*   Updated: 2022/02/10 16:24:22 by elabasqu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd(t_struct *s, char *str)
{
	int		n;
	char	**cmd;

	n = 0;
	if (s->data.env_path)
	{
		cmd = malloc(sizeof(char **) * (ft_super_strlen(s->data.env_path) + 1));
		if (access(str, F_OK) == 0)
			return (1);
		while (s->data.env_path[++n])
		{
			cmd[n] = ft_strjoin(s->data.env_path[n], "/");
			cmd[n] = ft_strjoin(cmd[n], str);
		}
		cmd[n] = 0;
		n = 0;
		while (cmd[n] && access(cmd[n], F_OK) != 0)
			n++;
		if (!cmd[n])
		{
			printf("Command not found: %s\n", str);
			return (0);
		}
		return (1);
	}
	printf("Command not found: %s\n", str);
	return (0);
}

int	ft_is_builtin(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	is_first_word_and_dollars(char *cmd, int i)
{
	while (i > 0 && cmd[i] == ' ')
		i--;
	while (i > 0 && cmd[i] != ' ' && cmd[i] != '|')
		i--;
	while (i > 0 && cmd[i] == ' ')
		i--;
	if (i != 0 && cmd[i] != '|')
		return (0);
	if (cmd[i] == '|')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] && cmd[i] != '$')
		return (0);
	return (1);
}

char	*first_word_fct(char *a_token)
{
	int		j;
	char	*first_word;

	j = 0;
	while (a_token[j] && a_token[j] != ' ')
		j++;
	if (a_token[j] == 0)
		return (NULL);
	first_word = malloc(sizeof(char) * (j + 1));
	if (first_word == NULL)
		return (NULL);
	j = 0;
	while (a_token[j] && a_token[j] != ' ')
	{
		first_word[j] = a_token[j];
		j++;
	}
	first_word[j] = 0;
	return (first_word);
}

char	*next_token(char *a_token)
{
	int		j;
	int		i;
	char	*first_word;

	i = 0;
	j = 0;
	while (a_token[j] && a_token[j] != ' ')
		j++;
	while (a_token[j] && a_token[j] == ' ')
		j++;
	i = j;
	while (a_token[j])
		j++;
	first_word = malloc(sizeof(char) * (j - i + 1));
	if (first_word == NULL)
		return (NULL);
	j = 0;
	while (a_token[i])
		add_char(first_word, a_token, &j, &i);
	first_word[j] = 0;
	return (first_word);
}
