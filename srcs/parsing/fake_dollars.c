#include "../../includes/minishell.h"

int	not_a_dollar(char *cmd, int i)
{
	i++;
	if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_' && cmd[i] != '?')
		return (0);
	return (1);
}

char	*fake_dollars(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;

	j = *i;
	(*i)++;
	while (cmd[*i] && cmd[*i] != ' ' \
			&& ft_is_chevron(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"' )
			skip_quote(cmd, cmd[*i], i);
		else
			(*i)++;
	}
	a_token = malloc(sizeof(char) * (*i - j + 10));
	if (a_token == NULL)
		return (NULL);
	*i = j;
	j = 0;
	add_char(a_token, cmd, &j, i);
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 \
			&& ft_is_quote(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
		add_char(a_token, cmd, &j, i);
	if (cmd[*i] != '$' && ft_is_quote(cmd[*i]) == 1)
		cpy_quote(a_token, cmd, &j, i, s);
	a_token[j] = 0;
	if (cmd[*i] == '$')
		return (fusion_double_token(a_token, cmd, i, s));
	return (a_token);
}
