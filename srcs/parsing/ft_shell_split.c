
#include "../../includes/minishell.h"

int	redirection(const char *s, char chevron, int *i)
{
	char quote;

	while (s[*i] == chevron || s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\'' || s[*i] == '\"' )
	{
		quote = s[*i];
		(*i)++;
		while (s[*i] != quote)
			(*i)++;
		while (s[*i] && s[*i] != ' ')
			(*i)++;
	}
	else
		while (s[*i] && s[*i] != ' ')
			(*i)++;
	return (1);
}

int	ft_countwords(const char *s)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '\'' || s[i] == '\"' )
		{
			skip_quote(s, s[i], &i);
			nb++;
		}
		if (s[i] == '>' || s[i] == '<')
			redirection(s, s[i], &i);
		else if (s[i] && s[i] != ' ')
			nb++;
		while (s[i] && s[i] != ' ')
			i++;
		if (s[i])
			i++;
	}
	return (nb);
}
/*
 * params	: la commande
 * return	: le nb de token
 * def		: skipe les spaces prend bien les quotes
 *			  ignore les chevron et nom des redirection
 *			  (">> lol" pas pris en compte)
 *			  norme rend degeu le else if et while devrais etre ensemble;
 */

int size_of_token(char *cmd, int i)
{
	int tmp;

	tmp = i;
	if (cmd[i] == '\'' || cmd[i] == '\"' )
	{
		skip_quote(cmd, cmd[i], &i);
		return (i - tmp);
	}
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (i - tmp);
}

char	*one_token(char *cmd, int *i)
{
	char	*a_token;
	char	quote;
	int		j;

	j = size_of_token(cmd, *i);
	a_token = malloc(sizeof(char) * (j + 1));
	if (a_token == NULL)
		return (NULL);
	j = 0;
	if (cmd[*i] == '\'' || cmd[*i] == '\"')
	{
		quote = cmd[*i];
		(*i)++;
		while (cmd[*i] != quote)
		{
			a_token[j] = cmd[*i];
			(*i)++;
			j++;
		}
	}
	while (cmd[*i] && cmd[*i] != ' ')
	{
			a_token[j] = cmd[*i];
			(*i)++;
			j++;
	}
	a_token[j] = 0;
	return (a_token);
}

char **split_shell(char *cmd)
{
	char	**token;
	int		i;
	int		word;

	token = malloc(sizeof(char *) * (ft_countwords(cmd) + 1));
	i = 0;
	word = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (ft_is_chevron(cmd[i]))
			redirection(cmd, cmd[i], &i);
		while (cmd[i] && cmd[i] == ' ')
			i++;
		token[word] = one_token(cmd, &i);
		if (token[word] == NULL)
			return (NULL);
		word++;
	}
	token[word] = 0;
	return (token);
}
