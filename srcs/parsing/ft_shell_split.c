
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
		if (ft_isalpha(s[i]))
		{
			while (s[i] && ft_isalpha(s[i]))
				i++;
			nb++;
		}
		else if (s[i] == ' ')
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
	}
	return (nb);
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
