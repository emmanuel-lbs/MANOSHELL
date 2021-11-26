
#include "../../includes/minishell.h"

int	ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_is_chevron(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	skip_quote(const char *s, char quote, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] != quote)
	{
		printf("missing one quote\n");
		return (-1);
	}
	(*i)++;
	printf("%s\n",&s[*i]);
	if (s[*i] && ft_is_quote(s[*i]) == 1)
		if (skip_quote(s, s[*i], i) == -1)
			return (-1);
	while (s[*i] && s[*i] != ' ' && ft_is_quote(s[*i]) == 0)
		(*i)++;
	printf("%s\n",&s[*i]);
	return (0);
}
