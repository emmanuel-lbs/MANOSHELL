
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

char	*pre_split(char *str)
{
	int i;
	char *command;

	i = 0;
	while (str[i] && !ft_is_chevron(str[i]) && str[i] != '|')
	{
		i++;
	}

	int j;

	j = 0;
	while (j <= i)
	{
		printf("%c",str[j]);
		j++;
	}

}

//void	(char *str)
//{
//
//	s->bob.token = ft_calloc(sizeof(char *), (ft_countwords(str, ' ') + 1));
//	if (!(tab))
//		return (NULL);
//}
//
//void	shell_split(char *str, t_struct *s)
//{
//	int		i;
//
//
//}
