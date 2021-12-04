
#include "../../includes/minishell.h"

t_bob	*lastbob(t_bob *bob)
{
	if (!bob)
		return (0);
	while (bob->next)
		bob = bob->next;
	return (bob);
}

void	add_back_bob(t_bob **bob, t_bob *add)
{

	if (*bob == NULL)
	{
		*bob = add;
		return ;
	}
}

t_bob	*ft_bobnew(char **str)
{
	t_bob *list;

	if (!(list = malloc(sizeof(*list))))
		return (0);
	list->token = str;
	list->next = NULL;
	return (list);
}
void	new_block(t_struct *s, char **token)
{
		int nb_word = 0;

		s->bob = malloc(sizeof(s->bob));
		s->bob->next = NULL;
		nb_word = 0;
		while (token[nb_word] && token[nb_word][0] != '|')
				nb_word++;
}
//
//void	printf_lst(t_bob *bob)
//{
//	int i;
//
//	while (bob->next != NULL)
//	{
//		while (
//	}
//}

/*
 * params	: la struct et l'input taper
 * return	: je sais pas encore/////////////////////////////////////////////////////////
 * def		: cree la liste chainer comportant les cmd de char ** les fd;
 */

int	fct(char **str, int start, int end, t_struct *s)
{
		int i;
		int word;

		s->bob = lastbob(s->bob);
		s->bob->token = malloc(sizeof(char *) * (end - start + 1));
		if (!s->bob->token)
				return (-1);

		word = 0;
		while (start <= end)
		{
				i = 0;
				while (str[word][i])
				{
						s->bob->token[start][i] = str[start][i];
						i++;
				}
				start++;
				word++;
		}
		return (0);
}

int	create_bob(t_struct *s, char **str)
{
		int j;

		j = 0;
		new_block(s, str);
		while (s->bob->token[j])
		{
				printf("==%s\n",s->bob->token[j]);
				j++;
		}

		int i;
		int start;
		int end;

		i = 0;
		start = 0;
		end = 0;
		while (str[i])
		{
				while (str[i] && str[i][0] != '|')
						i++;
				end = i;
				if (fct(str, start, end, s) == -1)
						return (-1);
				end += 2;
				start = end;
				//		add_back_bob(&s->bob.next, new_block(cmd));
		}
		return (0);
}
