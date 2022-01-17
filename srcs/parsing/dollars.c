
#include "../../includes/minishell.h"

int	len_env(char *env)
{
		int i;

		i = 0;
		while (env[i] && env[i] != '=')
				i++;
		return (i);
}

int	search_dollars(char *dollars, t_struct *s)
{
		s->env = s->first;
		while (s->env.next != NULL)
		{
				if (s->env.content)
						if (ft_strncmp(dollars, s->env.content, len_env((char *)s->env.content)) == 0)
								return (1);
				s->env = *s->env.next;
		}
		return (-1);
}

int	strlen_var_env(char *var)
{
		int i;
		int ret;

		i = 0;
		ret = 0;
		while (var[i] && var[i] != '=')
			i++;
		ret = i + 1;
		while (var[ret])
				ret++;
		return (ret - i + 1);
}

char *change_dollars(char *dollars, char *var)
{

		int i;
		int j;
		char *a_token;

		i = 0;
		j = 0;

		a_token = malloc(sizeof(char) * (strlen_var_env(var) + 1));
		while (var[i] && var[i] != '=')
			i++;
		if (var[i])
				i++;
		while (var[i])
		{
				if (var[i] == ' ')
				{
						add_char(a_token, var, &j, &i);
						while (var[i] == ' ')
								i++;
				}
				add_char(a_token, var, &j, &i);
		}
		a_token[j] = 0;
		free(dollars);
		return (a_token);
}


char *dollars_num(char *cmd)
{
		int i;
		char *token;

		i = 0;
		while (ft_isdigit(cmd[i]) == 1)
				i++;
		token = malloc(sizeof(char) * (i + 1));
		if (token == NULL)
				return (NULL);
		i = 0;
		while (ft_isdigit(cmd[i]) == 1)
		{
				token[i] = cmd[i];
				i++;
		}
		token[i] = 0;
		return (token);
}

char *one_token_dollars(char *cmd, int *i)
{
		char *token;
		int ret;

		(*i)++;
		if (ft_isdigit(cmd[*i]) == 1)
				return (dollars_num(&cmd[*i])); // c'est faux ca nan si $8795478654 alors juste $8 skip je crois
		ret = *i;
		while (ft_isalnum(cmd[*i]) == 1) //&& stop a caract speciaux notament quotes
				(*i)++;
		token = malloc(sizeof(char) * (*i - ret + 1));
		if (token == NULL)
				return (NULL);
		*i = ret;
		ret = 0;
		while (cmd[*i] != 0 && ft_isalnum(cmd[*i]) == 1) //&& stop a caract speciaux notament quotes
		{
				add_char(token, cmd, &ret, i);
		}
		token[ret] = 0;
		return (token);
}

int	diff_in_var_env(char *var)
{
		int i;
		int firstlen;
		int	secondlen;

		i = 0;
		while (var[i] && var[i] != '=')
				i++;
		firstlen = i;
		while (var[i])
				i++;
		secondlen = i - firstlen - 1;
		return (secondlen - firstlen);
}

int		resize_len_for_dollar(char *cmd, int start, int end, t_struct *s)
{
		int		diff;
		char	quote;
		char	*dollars;

		quote = cmd[start];
		start++;
		diff = 0;
		while (cmd[start] != quote && start < end)
		{
				if (cmd[start] == '$' && quote != '\'')
				{
						start++;
						dollars = one_token_dollars(cmd, &start);
						//						if (dollars == NULL)
						//							next
						search_dollars(dollars, s);
						diff += diff_in_var_env(s->env.content);
				}
				start++;
		}
		while (cmd[start] && start <= end && cmd[start] != ' ' && ft_is_quote(cmd[start]) != 1)
				start++;
		return (diff);
}
