//
//#include "../../includes/minishell.h"
//
//t_bob	*lastbob(t_bob *bob)
//{
//		if (!bob)
//				return (0);
//		while (bob->next)
//				bob = bob->next;
//		return (bob);
//}
//
//void	add_back_bob(t_bob **bob, t_bob *add)
//{
//
//		if (*bob == NULL)
//		{
//				*bob = add;
//				return ;
//		}
//}
//
//t_bob	*new_bob(void)
//{
//		t_bob *list;
//
//		list = malloc(sizeof(*list));
//		if (!list)
//				return (0);
//		list->next = NULL;
//		list->fd_in = 0;
//		list->fd_out = 0;
//		list->mode_out = 0;
//		return (list);
//}
//void	new_block(t_struct *s, char **token)
//{
//		int nb_word = 0;
//
//		nb_word = 0;
//		while (token[nb_word] && token[nb_word][0] != '|')
//				nb_word++;
//}
////
////void	printf_lst(t_bob *bob)
////{
////	int i;
////
////	while (bob->next != NULL)
////	{
////		while (
////	}
////}
//
///*
// * params	: la struct et l'input taper
// * return	: je sais pas encore/////////////////////////////////////////////////////////
// * def		: cree la liste chainer comportant les cmd de char ** les fd;
// */
//
//char	*one_token_for_bob(char *str)
//{
//		int i;
//		int j;
//		char *a_token;
//
//		i = 0;
//		j = 0;
//		a_token = malloc(sizeof(char) * (ft_strlen(str) + 1));
//		if (!a_token)
//				return (-1);
//		while (str[i])
//		{
//				a_token[j] = str[i];
//				i++;
//				j++;
//		}
//		a_token = 0;
//
//
//		/*
//		 * retirer les quotes, intepreter les $
//		 */
//
//
//		return (a_token);
//
//}
//
//void	gere_chevron(char *str, int actual_word, t_bob *bob)
//{
//		if (str[actual_word][0] = '>')
//		{
//				if (bob->fd_out != 0)
//						close(bob->fd_out);
//				if (!str[actual_word][1])
//						bob->mode_out = 1;
//				else
//						bob->mode_out = 2;
//				actual_word++;
//
//		}
//		else if (str[actual_word][0] = '<')
//		{
//				if (bob->fd_in != 0)
//						close(bob->fd_in);
//				//				if (!str[actual_word][1])
//				//						bob->mode_in = 1;
//				//				else
//				//ft_heredocs ????
//		}
//}
//
//int	fct(char **str, int start, int end, t_bob *bob)
//{
//		int i;
//		int word;
//
//		bob = lastbob(bob);
//		bob->token = malloc(sizeof(char *) * (end - start + 1));
//		if (!bob->token)
//				return (-1);
//
//		word = 0;
//		while (start < end)
//		{
//				if (ft_is_chevron(str[start][0]))
//				{
//						gere_chevron(str, start, bob);
//						start++;
//				}
//				else
//				{
//						bob->token[word] = one_token_for_bob(str[start]);
//						word++;
//				}
//				start++;
//		}
//		bob->token[word] = 0;
//		printf("oe\n");
//		return (0);
//}
//
//t_bob	*create_bob(char **str)
//{
//		t_bob *bob;
//		int i;
//		int start;
//		int end;
//
//		i = 0;
//		start = 0;
//		end = 0;
//		bob = malloc(sizeof(*bob));
//		bob->next = NULL;
//
//		int j;
//		while (str[end])
//		{
//				while (str[end] && str[end][0] != '|')
//						end++;
//				fct(str, start, end, bob);
//				if (str[end])
//						bob->next = new_bob();
//				if (str[end] && str[end][0] == '|')
//						end += 1;
//				start = end;
//
//				j = 0;
//				while (bob->token[j])
//				{
//						printf("%s\n",bob->token[j]);
//						j++;
//				}
//				//		add_back_bob(&s->bob.next, new_block(cmd));
//		}
//
//		i = 0;
//		return (bob);
//}
