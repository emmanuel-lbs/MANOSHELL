#include "../../includes/minishell.h"

static int    is_cmd(t_struct *s, char *str)
{
    int		n;
    char	**test;


    n = 0;
    if (s->data.env_path)
	{
		test = malloc (sizeof(char**) * ft_super_strlen(s->data.env_path));
		if (access(str, F_OK) == 0)
			return (1);
		while (s->data.env_path[++n])
		{
			test[n] = ft_strjoin(s->data.env_path[n], "/");
			test[n] = ft_strjoin(test[n], str);
		}
		n = 0;
		printf("ALO 1 \n");
		while (access(test[n], F_OK) != 0 && test[n])
			n++;
		printf("ALO 2 \n");
		if (!test[n])
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

int	is_first_word(char *cmd, int i)
{
	while (i > 0 && (cmd[i] != ' ' || cmd[i] != '|'))
		i--;
	while (i > 0 && (cmd[i] == ' ' || cmd[i] != '|'))
		i--;
	if (i == 0 || cmd[i] == '|')
		return (1);
	return (0);
}

void	modif_first_token(char *cmd, int i, char *a_token, t_struct *s)
{
	int		j;
	char	*first_word;

	j = 0;
	if (is_first_word(cmd, i) == 0)
		return ;
	while (a_token[j] && a_token[j] != ' ')
		j++;
	if (a_token[j] == 0)
		return ;
	first_word = malloc(sizeof(char) * (j + 1));
	if (first_word == NULL)
		return; //ernor = -1;
	j = 0;
	while (a_token[j] && a_token[j] != ' ')
	{
		first_word[j] = a_token[j];
		j++;
	}
	first_word[j] = 0;
	if (ft_is_builtin(first_word) == 1)
		printf("no 1\n");
	printf("ALO\n");
	if (is_cmd(s, first_word) == 1)
		printf("no 2\n");


}
