
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

//char	*pre_split(char *str)
//{
//	int i;
//	char *command;
//
//}
//
//int	cut_cmd()
//{
//}
//
//int	create_bob(t_struct *s, char *str)
//{
//	int word;
//	char *cmd;
//
//	word = cut_word(&cmd, str);
//	s->lst = lst_new(new_block(cmd));
//	while (str[i])
//	{
//		free(cmd);
//		i = cut_cmd(&cmd, &str[i]);
//		lst_add_back(s->lst, ft_lstnew(new_block(cmd)));
//	}
//	free(cmd);
//}
