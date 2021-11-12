
#include "../includes/minishell.h"

int	ft_countwords(const char *s, char c)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] && s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
			nb++;
		}
		else if (s[i] && s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			nb++;
		}
		i++;
	}
	return (nb);
}

/*char	**shell_split(char *str)
{
	int		i;
	char	**token;

	token = ft_calloc(sizeof(char *), (ft_countwords(str, ' ') + 1));
	if (!(tab))
		return (NULL);
	return (token);
}*/
