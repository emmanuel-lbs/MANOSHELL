
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
		(*i)++;
		if (s[*i] == '\'' || s[*i] == '\"')
			skip_quote(s, s[*i], i);
		while (s[*i] && s[*i] != ' ')
			(*i)++;
	}
	return (0);
}
