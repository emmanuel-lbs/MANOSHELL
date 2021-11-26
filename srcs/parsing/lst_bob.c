
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

t_bob	*new_block(char *str)
{
	t_bob *bob;
	bob = malloc(sizeof(t_bob *));
	bob->token = split_shell(str);
	return (bob);
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
