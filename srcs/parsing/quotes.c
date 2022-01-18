#include "../../includes/minishell.h"

char	*one_token(char *cmd, int *i, t_struct *s);

void	dollar_in_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s)
{
	char	*dollars;
	int		k;

	k = 0;
	dollars = one_token(cmd, j, s);
	while (dollars[k])
		add_char(cpy, dollars, i, &k);
	cpy[*i] = 0;
	free(dollars);
}

void	cpy_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s)
{
	char	quote;

	quote = cmd[*j];
//	add_char(cpy, cmd, i, j);
			(*j)++;
	while (cmd[*j] && cmd[*j] != quote)
	{
		if (cmd[*j] == '$' && quote == '\"')
			dollar_in_quote(cpy, cmd, i, j, s);
		else
			add_char(cpy, cmd, i, j);
	}
			(*j)++;
//	add_char(cpy, cmd, i, j);
	if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
		cpy_quote(cpy, cmd, i, j, s);
	if (cmd[*j] && cmd[*j] == '$')
	{
		dollar_in_quote(cpy, cmd, i, j, s);
	}
	while (cmd[*j] && cmd[*j] != ' ' && ft_is_chevron(cmd[*j]) == 0 && ft_is_quote(cmd[*j]) == 0 && cmd[*j] != '|')
		add_char(cpy, cmd, i, j);
	if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
		cpy_quote(cpy, cmd, i, j, s);
	cpy[*i] = 0;
}

int	verif_quote(char *cmd, int i)
{
	int		j;
	char	quote;
	int		signification;

	j = 0;
	if (ft_is_quote(cmd[i]) != 1)
		return (0);

	while (cmd[j] && j < i)
	{
		while (j < i && cmd[j] && ft_is_quote(cmd[j]) != 1)
			j++;
		signification = 0;
		quote = cmd[j];
		j++;
		while (j < i && cmd[j] && cmd[j] != quote)
			j++;
		if (j <= i && cmd[j] == quote)
		{
			signification = 1;
			j++;
		}
	}
	return (signification);
}

int	number_of_quote(char *cmd, int start, int end)
{
	char	quote;
	int		nb_quote;

	nb_quote = 0;
	while(start < end)
	{
		if (ft_is_quote(cmd[start]) == 1)
		{
			quote = cmd[start];
			start++;
			nb_quote += 2;
			while (cmd[start] != quote)
				start++;
			start++;
		}
		else
			start++;
	}
	return (nb_quote);
}

char	*one_token_quote(char *cmd, int *i, t_struct *s)
{
	char	*a_token;
	int		start;
	int		end;

	start = *i;
	skip_quote(cmd, cmd[*i], i);
	end = *i;
	*i += resize_len_for_dollar(cmd, start, end, s);
	*i -= number_of_quote(cmd, start, end);
	a_token = malloc(sizeof(char) * (*i - start + 1));
	if (a_token == NULL)
		return (NULL);
	*i = start;
	start = 0;
	cpy_quote(a_token, cmd, &start, i, s);
	return (a_token);
}

