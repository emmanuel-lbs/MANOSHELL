
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
	lastbob(*bob)->next = add;
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
		//	while (str[i])
		//	{
		//		free(cmd);
		//		cmd = cut_cmd(str , &i);
		//		s->bob.token = split_shell(cmd);;
		//		j = 0;
		//		while (s->bob.token[j])
		//		{
		//			printf("%s\n", s->bob.token[j]);
		//			j++;
		//		}
		//		//		add_back_bob(&s->bob.next, new_block(cmd));
		//	}
		return (0);
}
