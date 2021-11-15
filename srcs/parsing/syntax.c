#include "../../includes/minishell.h"

int	ft_is_chevron(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	chevron(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_chevron(str[i]))
		i++;
	if (i > 2)
	{
		if (str[i] == 0)
			i--;
		if (str[0] == '<' && str[1] == '<' && str[2] == '<')
			printf("this operator is not support `<<<' \n");
		else
			printf("syntax error near unexpected token `%c'\n", str[i]);
		return (-1);
	}
	if (i == 2 && str[0] != str[1])
	{
		printf("syntax error near unexpected token `%c'\n", str[1]);
		return (-1);
	}
	while (str[i] && ft_is_ispaces(str[i]))
		i++;
	if (str[i] && (ft_is_chevron(str[i]) || str[i] == '|'))
	{
		printf("syntax error near unexpected token `%c'\n", str[i]);
		return (-1);
	}
	return (0);
}
/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	vas les erreur de syntax "<<< << <> >< <| >|"
 */

int	specific_case_syntax(char *str)
{
	if (str[0] == '|')
	{
		printf("syntax error near unexpected token `%c'\n", str[0]);
		return (-1);
	}
	if (str[ft_strlen(str) - 1] == '|')
	{
		printf("syntax error near unexpected token");
		printf(" `%c'\n", str[ft_strlen(str) - 1]);
		return (-1);
	}
	if (ft_is_chevron(str[ft_strlen(str) - 1]))
	{
		printf("syntax error near unexpected token");
		printf(" `%c'\n", str[ft_strlen(str) - 1]);
		return (-1);
	}
	return (0);
}
/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	vas check la syntax premier et dernier caracteres
 */

int	operator_support(char c)
{
	if (c == '&')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}

int	check_operator(char *str)
{
	int i;

	i = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' )
		{
			if (skip_quote(str, str[i], &i) == -1)
				return (-1);
		}
		if (operator_support)
		{
			printf("syntax error near unexpected token `%c'\n", str[i]);
			return (-1);
		}
		i++;
	}
}

int	command_syntax(char *str)
{
	int	i;

	i = 0;
	if (check_operator(str) == -1)
	{
		return (-1);
	}
	if (specific_case_syntax(str) == -1)
		return (-1);
	while (str[i])
	{
		if (ft_is_chevron(str[i]))
		{
			if (chevron(&str[i]) == -1)
				return (-1);
		}
		if (str[i] == '\'' || str[i] == '\"' )
		{
			if (skip_quote(str, str[i], &i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	vas check la syyntax de chaques commande
 */
