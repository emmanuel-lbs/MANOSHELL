
#include "../../includes/minishell.h"

int	skip_quote(const char *s, char quote, int *i)
{
	if (s[*i] && s[*i] == quote)
	{
		(*i)++;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] != quote)
		{
			printf("missing one quote\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_countwords(const char *s)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
		}
		else if (s[i] == '\'' || s[i] == '\"' )
		{
			skip_quote(s, s[i], &i);
			while (s[i] && s[i] != ' ')
				i++;
			nb++;
		}
		else if (ft_isprint(s[i]))
		{
			while (s[i] && ft_isprint(s[i]) && s[i] != ' ')
				i++;
			nb++;
		}
		if (s[i] != 0)
			i++;
	}
	return (nb);
}

char *cut_cmd(char *str, int *i)
{
	char *cmd;
	int tmp;
	int j;

	j = 0;
	tmp = *i;
	while (str[*i] && str[*i] != '|')
	{
		j++;
		(*i)++;
	}
	cmd = malloc(sizeof(char) * (j + 1));
	*i = tmp;
	j = 0;
	while (str[*i] && str[*i] != '|')
	{
		cmd[j] = str[*i];
		(*i)++;
		j++;
	}
	cmd[j] = 0;
	(*i)++;
	return (cmd);
}

int	create_bob(t_struct *s, char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = cut_cmd(str , &i);
	printf("%s\nnb de token = %d\n",cmd, ft_countwords(cmd));
//	printf("%p", s->bob->next);
//	new_block(s, cmd);
	while (str[i])
	{
		free(cmd);
		cmd = cut_cmd(str , &i);
		add_back_bob(&s->bob.next, new_block(cmd));
	}
	return (0);
}
