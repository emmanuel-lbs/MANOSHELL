
#include "../includes/minishell.h"

int parsing(char *str, t_struct *s)
{



}

int		skip_quote(const char *s, char quote, int *i)
{
	if (s[*i] && s[*i] == quote)
	{
		(*i)++;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] != quote)
		{
			printf("missing one quote\n");
			return(-1);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

static int	ft_countwords(const char *s)
{
	int	nb;
	int i;

	i = 0;
	nb = 0;
	if (s[i] && s[i] != ' ')
	{
		nb++;
		i++;
	}
	while (s[i])
	{
		//		printf("%c",s[i]);
		if (s[i] && s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
			if (s[i] && s[i] != ' ')
				nb++;
		}
		else if (s[i] && s[i] == 34)
			nb += skip_quote(s, 34, &i);
		else if (s[i] && s[i] == 39)
			nb += skip_quote(s, 39, &i);
		else
			i++;
	}
	return (nb);
}
