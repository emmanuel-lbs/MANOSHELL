#include "../../includes/minishell.h"

static int    is_cmd(t_struct *s, char *str)
{
    int		n;
    char	**test;


    n = 0;
    if (s->data.env_path)
	{
		test = malloc (sizeof(char**) * (ft_super_strlen(s->data.env_path) + 1));
		if (access(str, F_OK) == 0)
			return (1);
		while (s->data.env_path[++n])
		{
			test[n] = ft_strjoin(s->data.env_path[n], "/");
			test[n] = ft_strjoin(test[n], str);
		}
		test[n] = 0;
		n = 0;
		while (test[n] && access(test[n], F_OK) != 0 )
			n++;
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

char *first_word_fct(char *a_token)
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
		return (NULL); //ernor = -1;
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
	int	j;
	int	i;
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
		return (NULL); //ernor = -1;
	j = 0;
	while (a_token[i])
		add_char(first_word, a_token, &j, &i);
	first_word[j] = 0;
	return (first_word);
}


int	should_i_modif_token(char *cmd, int i, char *a_token, t_struct *s)
{
	char	*first_word;

	if (is_first_word_and_dollars(cmd, i) == 0)
		return (0);
	first_word = first_word_fct(a_token);
	if (first_word == NULL)
		return (0);
	if (!(ft_is_builtin(first_word) == 1 || is_cmd(s, first_word) == 1))
		return (0);
	return (1);

}

void	modif_token(char *a_token, char **lst_tkn, int *nb_word)
{
	char	*first_word;

	first_word = first_word_fct(a_token);
	lst_tkn[*nb_word] = first_word;
	(*nb_word)++;
	lst_tkn[*nb_word] = next_token(a_token);
}
