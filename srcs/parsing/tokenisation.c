
#include "../../includes/minishell.h"

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
				if (ft_is_chevron(s[i]) == 1)
				{
						while (ft_is_chevron(s[i]) == 1)
								i++;
						nb++;
				}
				if (s[i] && s[i] != ' ')
						nb++;
				while (s[i] && s[i] != ' ')
				{
						if (s[i] && ft_is_quote(s[i]) == 1)
						{
								skip_quote(s, s[i], &i);
								nb++;
						}
						else if (s[i] && ft_is_chevron(s[i]) == 1)
						{
								nb++;
								while (s[i] && ft_is_chevron(s[i]) == 1)
										i++;
								if (s[i] && s[i] != ' ' && ft_is_quote(s[i]) == 0 && ft_is_chevron(s[i]) == 0)
										nb++;
						}
						else
								i++;
				}
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
		if (ft_is_chevron(cmd[i]) == 1)
		{
				if (ft_is_chevron(cmd[i + 1]) == 1)
						return (2);
				return (1);
		}
		while (cmd[i] && cmd[i] != ' ')
		{
				if (cmd[i] == '\'' || cmd[i] == '\"' )
				{
						skip_quote(cmd, cmd[i], &i);
						return (i - tmp);
				}
				else if (ft_is_chevron(cmd[i]) == 1)
						return (i - tmp);
				else
						i++;
		}
		return (i - tmp);
}

void	cpy_quote(char *cpy, char *cmd, int *i, int *j)
{
		char quote;

		if (ft_is_quote(cmd[*j]) == 1)
		{
				quote = cmd[*j];
				cpy[*i] = quote;
				(*j)++;
				(*i)++;
				while (cmd[*j] && cmd[*j] != quote)
				{
						cpy[*i] = cmd[*j];
						(*j)++;
						(*i)++;
				}
				cpy[*i] = quote;
				(*j)++;
				(*i)++;
		}
		if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
				cpy_quote(cpy, cmd, i, j);
		while (cmd[*j] && cmd[*j] != ' ' && ft_is_chevron(cmd[*j]) == 0 && ft_is_quote(cmd[*j]) == 0)
		{
				cpy[*i] = cmd[*j];
				(*j)++;
				(*i)++;
		}
		if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
				cpy_quote(cpy, cmd, i, j);
}

int	cpy_chevron(char *cpy, char *cmd, int *i)
{
		int j;

		j = 0;
		if (cmd[*i] == '>')
		{
				cpy[j] = cmd[*i];
				(*i)++;
				j++;
				if (cmd[*i] == '>')
				{
						cpy[j] = cmd[*i];
						(*i)++;
						j++;
				}
		}
		else if (cmd[*i] == '<')
		{
				cpy[j] = cmd[*i];
				(*i)++;
				j++;
				if (cmd[*i] == '<')
				{
						cpy[j] = cmd[*i];
						(*i)++;
						j++;
				}
		}
		cpy[j] = 0;
		return (j);
}

char	*one_token(char *cmd, int *i)
{
		char	*a_token;
		int		j;

		a_token = malloc(sizeof(char) * (size_of_token(cmd, *i) + 1));
		if (a_token == NULL)
				return (NULL);
		j = 0;
		if (ft_is_chevron(cmd[*i]) == 1)
		{
				j = cpy_chevron(a_token, cmd, i);
				return (a_token);
		}
		else if (ft_is_quote(cmd[*i]) == 1)
				cpy_quote(a_token, cmd, &j, i);
		while (cmd[*i] && cmd[*i] != '|' && cmd[*i] != ' ' && ft_is_quote(cmd[*i]) == 0)
		{
				if (cmd[*i] && ft_is_chevron(cmd[*i]) == 1)
				{
						a_token[j] = 0;
						return (a_token);
				}
				a_token[j] = cmd[*i];
				(*i)++;
				j++;
		}
		if (ft_is_quote(cmd[*i]) == 1)
				cpy_quote(a_token, cmd, &j, i);
		a_token[j] = 0;
		return (a_token);
}


char **split_shell(char *cmd)
{
		char	**token;
		int		i;
		int		word;

		token = malloc(sizeof(char *) * (ft_countwords(cmd) + 1));
		if (token == NULL)
				return (NULL);
		i = 0;
		word = 0;
		while (cmd[i])
		{
				while (cmd[i] && cmd[i] == ' ')
						i++;
				token[word] = one_token(cmd, &i);
				if (token[word] == NULL)
				{
						//free
						return (NULL);
				}
				word++;
		}
		token[word] = 0;
		return (token);
}
