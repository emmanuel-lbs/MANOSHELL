
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
						if (s[i] && s[i] == '|' && (s[i - 1] != ' ' || s[i + 1] != ' '))
						{
								if (s[i - 1] != ' ' && s[i + 1] != ' ')
										nb++;
								nb++;
						}
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
						{
								i++;
						}
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

void	cpy_quote(char *cmd)
{
		char	quote;
		char	*a_token;
		int i;

		i = 0;
		skip_quote(cmd, cmd[i], &i);
		a_token = malloc(sizeof(char) * (i + 1));
		if (a_token == NULL)
				return (NULL);
		i = 0;
		quote = cmd[i];
		cpy[i] = quote;
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

char	*cpy_chevron(char *cmd)
{
		int i;
		char *a_token;

		i = 1;
		if (ft_is_chevron(cmd[i]) == 1)
				i++;
		a_token = malloc(sizeof(char) * (i + 1));
		if (a_token == NULL)
				return (NULL);
		i = 0;
		a_token[i] = cmd[i];
		i++;
		if (ft_is_chevron(cmd[i]) == 1)
		{
				a_token[i] = cmd[i];
				i++;
		}
		a_token[i] = 0;
		return (a_token);
}

char	*one_token(char *cmd, int *i)
{
		char	*a_token;
		int		j;

		if (ft_is_chevron(cmd[*i]) == 1)
				a_token = cpy_chevron(&cmd[*i]);
		else if (ft_is_quote(cmd[*i]) == 1)
				a_token = cpy_quote(&cmd[*i]);
		else if (cmd[*i] == '$')
				a_token = token_dollars(&cmd[*i]);
		else if (cmd[&i] == '|')
		{
				a_token = malloc(sizeof(char) * 2);
				if (a_token = NULL)
						return (NULL);
				a_token[0] = '|';
				a_token[1] = 0;
		}
		else
				normal_token();

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
		if (cmd[*i] && ft_is_quote(cmd[*i]) == 1)
				cpy_quote(a_token, cmd, &j, i);
		if (cmd[*i] && cmd[*i] == '|' && j == 0)
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
		if (token == NULL)
				return (NULL);
		printf("countword =%d\n",ft_countwords(cmd) + 1);
		i = 0;
		word = 0;
		while (cmd[i])
		{
				while (cmd[i] && cmd[i] == ' ')
						i++;
				if (cmd[i])
				{
						token[word] = one_token(cmd, &i);
						if (token[word] == NULL)
						{
								//free
								return (NULL);
						}
						word++;
				}
		}
		token[word] = 0;
		return (token);
}
