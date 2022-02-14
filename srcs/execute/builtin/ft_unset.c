#include "../../../includes/minishell.h"

int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(t_struct *s)
{
	int		i;
	int		j;
	t_list	*mem;
	t_list	*tmp;

	s->env = s->first;
	i = 1;
	j = 0;
	while (s->bob->token[i] != NULL)
	{
		if (!ft_isalpha_(s->bob->token[i][0]))
		{
			g_errna = 1;
			printf("unset: \'%s\': not a valid identifier\n", s->bob->token[i]);
		}
		else
		{
			while (s->bob->token[i][j])
			{
				if (!ft_isalnum_(s->bob->token[i][j]))
				{
					g_errna = 1;
					printf("unset: \'%s\': not a valid identifier\n", s->bob->token[i]);
				}
				j++;
			}
			if (!s->bob->token[i][j])
			{
				while (s->env->next != NULL)
				{
					if (ft_strncmp(s->env->content, s->bob->token[i], ft_strclen(s->env->content, '=')) == 0)
					{
						if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
							s->old_pwd.content = NULL;
						else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
							s->data.env_path = NULL;
						else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
							s->home.content = NULL;
						s->first = s->first->next;
						ft_delfirst(&s->env);
						g_errna = 0;
						break ;
					}
					if (ft_strncmp(s->env->next->content, s->bob->token[i], ft_strclen(s->env->next->content, '=')) == 0)
					{
						if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
							s->old_pwd.content = NULL;
						else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
							s->data.env_path = NULL;
						else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
							s->home.content = NULL;	
						ft_delone(&s->env);
						g_errna = 0;
						break ;
					}
					else
					{
						if (ft_strcmp(s->env->next->content, s->bob->token[i]) == 0)
						{
							if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
								s->old_pwd.content = NULL;
							else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
								s->data.env_path = NULL;
							else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
								s->home.content = NULL;
							ft_delone(&s->env);
							g_errna = 0;
							break ;
						}
					}
					s->env = s->env->next;
				}
			}
		}
		i++;
	}
}
