#include "../../../includes/minishell.h"

void	ft_delone(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp->next;
	tmp->next = tmp->next->next;
	free(mem);
}

void	ft_delfirst(t_list **lst)
{
	t_list	*tmp;
	t_list	*mem;

	tmp = *lst;
	mem = tmp;
	tmp = tmp->next;
	free(mem);
}

int	ft_isalpha_(int c)
{
	if ((65 <= c && c <= 90) || (97 <= c && c <= 122) || c == '_')
		return (1);
	return (0);
}

int	ft_isalnum_(int c)
{
	if (ft_isalpha_(c) || ft_isdigit(c))
		return (1);
	return (0);
}

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
			printf("unset: \'%s\': not a valid identifier\n", s->bob->token[i]);
		}
		else
		{
			while (s->bob->token[i][j])
			{
				if (!ft_isalnum_(s->bob->token[i][j]))
				{
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
						printf("1: next = %s\n", s->env->content);
						if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
						{
							s->old_pwd.content = NULL;
						}
						else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
						{
							s->data.env_path = NULL;
						}
						else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
						{
							s->home.content = NULL;
						}
						s->first = s->first->next;
						ft_delfirst(&s->env);
						break ;
					}
					if (ft_strncmp(s->env->next->content, s->bob->token[i], ft_strclen(s->env->next->content, '=')) == 0)
					{
						if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
						{
							s->old_pwd.content = NULL;
						}
						else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
						{
							s->data.env_path = NULL;
						}
						else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
						{
							s->home.content = NULL;
						}						
						printf("2: next = %s\n", s->env->next->content);
						ft_delone(&s->env);
						break ;
					}
					else
					{
						if (ft_strcmp(s->env->next->content, s->bob->token[i]) == 0)
						{
							if (ft_strncmp(s->env->next->content, "OLDPWD=", 5) == 0)
							{
								s->old_pwd.content = NULL;
							}
							else if (ft_strncmp(s->env->next->content, "PATH=", 5) == 0)
							{
								s->data.env_path = NULL;
							}
							else if (ft_strncmp(s->env->next->content, "HOME=", 5) == 0)
							{
								s->home.content = NULL;
							}							
							printf("3: next = %s\n", s->env->next->content);
							ft_delone(&s->env);
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
