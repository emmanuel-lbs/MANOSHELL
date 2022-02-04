#include "../../includes/minishell.h"

int	is_heredocs(t_struct *s)
{
	int i;

	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		i = 0;
		while (s->bob->token[i])
		{
			if (s->bob->token[i][0] == '<' && s->bob->token[i][1] == '<')
			{
				s->bob = s->first_bob;
				return (1);
			}
			i++;
		}
		s->bob = s->bob->next;
	}
	s->bob = s->first_bob;
	return (0);
}

char	*heredocs_end_word(char	**token, int i)
{
	while (token[i] && strcmp("<<", token[i]) != 0)
		i++;
	if (token[i] && strcmp("<<", token[i]) != 0)
		return (NULL);
	return (token[i + 1]);
}

t_bob	*heredocs_bob(t_bob *bob)
{
	int i;

	while (bob != NULL)
	{
		i = 0;
		while (bob->token[i] && strcmp("<<", bob->token[i]) != 0)
			i++;
		if (bob->token[i] && strcmp("<<", bob->token[i]) == 0)
			return (bob);
		bob = bob->next;
	}
	printf("error\n");
	exit(-1);
	return (bob);;
}

void	heredocs(t_bob *bob, char	*end_word)
{
	char	*str;

	str = "";
	str = readline("<<");
	if (str == 0 || strcmp(str, end_word) == 0)
	{
		bob->heredocs = ft_strdup("");
		return ;
	}
	bob->heredocs = ft_strjoin(str, "\n");
	free(str);
	while (1)
	{
		str = readline("<<");
		if (str == 0 || strcmp(str, end_word) == 0)
			return ;
		bob->heredocs = ft_strjoin(bob->heredocs, str);
		bob->heredocs = ft_strjoin(bob->heredocs, "\n");
		free(str);
	}
}

void	beging_hered(char	**str, int actual_word, t_bob *bob)
{
	if (bob->mode_in == 2)
		free(bob->heredocs);
	heredocs(bob, heredocs_end_word(str, actual_word));
}
