
#include "../../includes/minishell.h"


char	**ft_splitone(char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = ft_calloc(sizeof(char *), (2 + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	j = 0;
	tab[0] = malloc(sizeof(char) * (len_jusque(s, c) + 1));
	if (tab[0] == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
		add_char(tab[0], s, &j, &i);
	tab[0][j] = 0;
	while (s[i] && s[i] != c)
		i++;
	j = i;
	while (s[i])
		i++;
	tab[1] = malloc(sizeof(char) * (i - j + 1));
	if (tab[1] == NULL)
		return (NULL);
	i = j;
	j = 0;
	while (s[i])
		add_char(tab[1], s, &j, &i);
	tab[1][j] = 0;
	tab[2] = 0;
	return (tab);
}
